// Stay Tuned Up Game


#include "Player/STU_Character.h"

#include "Animations/STU_AnimUtility.h"
#include "Components/CapsuleComponent.h"
#include "Components/STU_CharacterMovementComponent.h"
#include "Components/STU_FallDamageComponent.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ASTU_Character::ASTU_Character(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTU_CharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(FName(TEXT("IgnoreOnlyPawn")));

	HealthComponent = CreateDefaultSubobject<USTU_HealthComponent>("HealthComponent");

	FallDamageComponent = CreateDefaultSubobject<USTU_FallDamageComponent>("FallDamageComponent");

	WeaponComponent = CreateDefaultSubobject<USTU_WeaponComponent>("WeaponComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called every frame
void ASTU_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetComponentFacePlayer(HealthTextComponent);
}

void ASTU_Character::Reset()
{
	WeaponComponent->StopZooming();
	WeaponComponent->StopFiring();

	Super::Reset();
}

void ASTU_Character::TurnOff()
{
	WeaponComponent->StopZooming();
	WeaponComponent->StopFiring();

	Super::TurnOff();
}

bool ASTU_Character::IsMovingForward() const
{
	return FVector::Coincident(GetActorForwardVector(), GetVelocity().GetSafeNormal(),
	                           FMath::Cos(FMath::DegreesToRadians(MaxRunAngle)));
}

void ASTU_Character::Run()
{
	bPressedRun = true;
}

void ASTU_Character::StopRunning()
{
	bPressedRun = false;
}

bool ASTU_Character::IsRunning() const
{
	return bPressedRun && IsMovingForward();
}

void ASTU_Character::SetPlayerColor(const FLinearColor& Color)
{
	const auto MaterialInstanceDynamic = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	if (!MaterialInstanceDynamic)
		return;

	MaterialInstanceDynamic->SetVectorParameterValue(MaterialColorName, Color);
}

// Called when the game starts or when spawned
void ASTU_Character::BeginPlay()
{
	Super::BeginPlay();

	OnCharacterMovementUpdated.AddDynamic(this, &ThisClass::HandleOnCharacterMovementUpdated);

	HealthComponent->OnDeath.AddDynamic(this, &ThisClass::HandleOnDeath);

	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::HandleOnHealthChanged);
	HandleOnHealthChanged(HealthComponent->GetHealth(), 0.0f);
}

void ASTU_Character::HandleOnDeath()
{
	WeaponComponent->OnOwnerDeath();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	//DetachFromControllerPendingDestroy();

	STU_AnimUtility::SetRagdoll(this, GetMesh());

	//PlayAnimMontage(DeathAnimMontage);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), DeathSound, GetActorLocation());

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpan);
}

void ASTU_Character::HandleOnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%0.0f"), Health)));
}

void ASTU_Character::HandleOnCharacterMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f IsRunning = %d"), UGameplayStatics::GetRealTimeSeconds(GetWorld()), IsRunning());

	IsRunning() ? WeaponComponent->LockWeapon() : WeaponComponent->UnlockWeapon();
}

void ASTU_Character::SetComponentFacePlayer(USceneComponent* SceneComponent) const
{
	const auto PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld());
	if (!PlayerController)
		return;

	const auto Pawn = PlayerController->GetPawnOrSpectator();
	if (!Pawn)
		return;

	SceneComponent->SetWorldRotation((-Pawn->GetActorRotation().Vector()).Rotation());
}
