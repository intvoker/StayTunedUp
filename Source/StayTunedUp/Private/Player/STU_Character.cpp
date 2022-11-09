// Stay Tuned Up Game


#include "Player/STU_Character.h"

#include "Animations/STU_AnimUtility.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STU_CharacterMovementComponent.h"
#include "Components/STU_FallDamageComponent.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTU_Character::ASTU_Character(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTU_CharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionProfileName(FName(TEXT("IgnoreOnlyPawn")));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTU_HealthComponent>("HealthComponent");

	FallDamageComponent = CreateDefaultSubobject<USTU_FallDamageComponent>("FallDamageComponent");

	WeaponComponent = CreateDefaultSubobject<USTU_WeaponComponent>("WeaponComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTU_Character::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddDynamic(this, &ThisClass::OnDeath);
	HealthComponent->OnDeath.AddDynamic(WeaponComponent, &USTU_WeaponComponent::OnOwnerDeath);

	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
}

// Called every frame
void ASTU_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTU_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ThisClass::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ThisClass::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ThisClass::StopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTU_WeaponComponent::StopFiring);

	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::SwitchWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::Reload);
}

bool ASTU_Character::IsMovingForward() const
{
	return FVector::Coincident(GetActorForwardVector(), GetVelocity().GetSafeNormal());
}

bool ASTU_Character::IsRunning() const
{
	return bPressedRun && IsMovingForward();
}

void ASTU_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTU_Character::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTU_Character::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASTU_Character::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASTU_Character::Run()
{
	bPressedRun = true;
}

void ASTU_Character::StopRunning()
{
	bPressedRun = false;
}

void ASTU_Character::OnDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	//DetachFromControllerPendingDestroy();

	STU_AnimUtility::SetRagdoll(this, GetMesh());

	//PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(LifeSpan);

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTU_Character::OnHealthChanged(float Health, float HealthDelta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%0.0f"), Health)));

	if (HealthDelta >= 0.0f)
		return;

	const auto PlayerController = GetController<APlayerController>();
	if (!PlayerController || !PlayerController->PlayerCameraManager)
		return;

	PlayerController->PlayerCameraManager->StartCameraShake(DamageCameraShakeClass);
}
