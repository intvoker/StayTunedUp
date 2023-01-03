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

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, WeaponComponent, &USTU_WeaponComponent::StopZooming);

	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::SwitchWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTU_WeaponComponent::Reload);
}

void ASTU_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponComponent->OnWeaponZoom.AddDynamic(this, &ThisClass::HandleOnWeaponZoom);
	WeaponComponent->OnWeaponStopZooming.AddDynamic(this, &ThisClass::HandleOnWeaponStopZooming);

	CameraCollisionSphereComponent->OnComponentBeginOverlap.AddDynamic(
		this, &ThisClass::HandleOnComponentBeginOverlapCameraCollision);
	CameraCollisionSphereComponent->OnComponentEndOverlap.AddDynamic(
		this, &ThisClass::HandleOnComponentEndOverlapCameraCollision);
}

void ASTU_PlayerCharacter::HandleOnDeath()
{
	Super::HandleOnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTU_PlayerCharacter::HandleOnHealthChanged(float Health, float HealthDelta)
{
	Super::HandleOnHealthChanged(Health, HealthDelta);

	if (HealthDelta >= 0.0f)
		return;

	const auto PlayerCameraManager = GetPlayerCameraManager();
	if (!PlayerCameraManager)
		return;

	PlayerCameraManager->StartCameraShake(DamageCameraShakeClass);
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

APlayerCameraManager* ASTU_PlayerCharacter::GetPlayerCameraManager() const
{
	const auto PlayerController = GetController<APlayerController>();
	if (!PlayerController)
		return nullptr;

	return PlayerController->PlayerCameraManager;
}

void ASTU_PlayerCharacter::HandleOnWeaponZoom(float ZoomFOV)
{
	const auto PlayerCameraManager = GetPlayerCameraManager();
	if (!PlayerCameraManager)
		return;

	DefaultFOV = PlayerCameraManager->GetFOVAngle();

	PlayerCameraManager->SetFOV(ZoomFOV);
}

void ASTU_PlayerCharacter::HandleOnWeaponStopZooming()
{
	const auto PlayerCameraManager = GetPlayerCameraManager();
	if (!PlayerCameraManager)
		return;

	PlayerCameraManager->SetFOV(DefaultFOV);
}

void ASTU_PlayerCharacter::HandleOnComponentBeginOverlapCameraCollision(UPrimitiveComponent* OverlappedComponent,
                                                                        AActor* OtherActor,
                                                                        UPrimitiveComponent* OtherComp,
                                                                        int32 OtherBodyIndex, bool bFromSweep,
                                                                        const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

void ASTU_PlayerCharacter::HandleOnComponentEndOverlapCameraCollision(UPrimitiveComponent* OverlappedComponent,
                                                                      AActor* OtherActor,
                                                                      UPrimitiveComponent* OtherComp,
                                                                      int32 OtherBodyIndex)
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
