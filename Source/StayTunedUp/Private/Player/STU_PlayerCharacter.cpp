// Stay Tuned Up Game


#include "Player/STU_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASTU_PlayerCharacter::ASTU_PlayerCharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	CameraCollisionSphereComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionSphereComponent");
	CameraCollisionSphereComponent->InitSphereRadius(10.0f);
	CameraCollisionSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CameraCollisionSphereComponent->SetupAttachment(CameraComponent);
}

// Called to bind functionality to input
void ASTU_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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

void ASTU_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraCollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCameraCollisionBeginOverlap);
	CameraCollisionSphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnCameraCollisionEndOverlap);
}

void ASTU_PlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTU_PlayerCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	Super::OnHealthChanged(Health, HealthDelta);

	if (HealthDelta >= 0.0f)
		return;

	const auto PlayerController = GetController<APlayerController>();
	if (!PlayerController || !PlayerController->PlayerCameraManager)
		return;

	PlayerController->PlayerCameraManager->StartCameraShake(DamageCameraShakeClass);
}

void ASTU_PlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTU_PlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTU_PlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ASTU_PlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASTU_PlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                         bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASTU_PlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASTU_PlayerCharacter::CheckCameraOverlap() const
{
	const auto bHide = CameraCollisionSphereComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(bHide);

	TArray<USceneComponent*> SceneComponentChildren;
	GetMesh()->GetChildrenComponents(true, SceneComponentChildren);

	for (const auto SceneComponentChild : SceneComponentChildren)
	{
		if (const auto PrimitiveComponentChild = Cast<UPrimitiveComponent>(SceneComponentChild))
		{
			PrimitiveComponentChild->SetOwnerNoSee(bHide);
		}
	}
}
