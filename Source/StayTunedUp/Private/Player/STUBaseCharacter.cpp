// Stay Tuned Up Game


#include "Player/STUBaseCharacter.h"

#include "Animations/STUAnimUtility.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUFallDamageComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/STUBaseWeapon.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(
		ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

	FallDamageComponent = CreateDefaultSubobject<USTUFallDamageComponent>("FallDamageComponent");

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddDynamic(this, &ThisClass::OnDeath);
	HealthComponent->OnDeath.AddDynamic(WeaponComponent, &USTUWeaponComponent::OnOwnerDeath);

	HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
	OnHealthChanged(HealthComponent->GetHealth());
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ThisClass::Turn);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ThisClass::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &ThisClass::StopJumping);

	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Pressed, this, &ThisClass::Run);
	PlayerInputComponent->BindAction("Run", EInputEvent::IE_Released, this, &ThisClass::StopRunning);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, WeaponComponent, &USTUWeaponComponent::Fire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, WeaponComponent, &USTUWeaponComponent::StopFiring);
}

void ASTUBaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUBaseCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTUBaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASTUBaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASTUBaseCharacter::Run()
{
	bPressedRun = true;
}

void ASTUBaseCharacter::StopRunning()
{
	bPressedRun = false;
}

void ASTUBaseCharacter::OnDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	DetachFromControllerPendingDestroy();

	STUAnimUtility::SetRagdoll(this, GetMesh());

	// PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	// SetLifeSpan(LifeSpanOnDeath);

	// if (Controller)
	// {
	// 	Controller->ChangeState(NAME_Spectating);
	// }
}

void ASTUBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%0.f"), Health)));
}

bool ASTUBaseCharacter::IsMovingForward() const
{
	return FVector::Coincident(GetActorForwardVector(), GetVelocity().GetSafeNormal());
}

bool ASTUBaseCharacter::IsRunning() const
{
	return bPressedRun && IsMovingForward();
}
