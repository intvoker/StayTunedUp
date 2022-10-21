// Stay Tuned Up Game


#include "Weapons/STU_Weapon.h"

#include "Animations/STU_AnimUtility.h"
#include "GameFramework/Character.h"

// Sets default values
ASTU_Weapon::ASTU_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void ASTU_Weapon::Fire()
{
	MakeShot();
}

void ASTU_Weapon::StopFiring()
{
}

void ASTU_Weapon::OnOwnerDeath()
{
	STU_AnimUtility::SetRagdoll(this, WeaponMesh);

	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	SetLifeSpan(LifeSpan);
}

// Called when the game starts or when spawned
void ASTU_Weapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTU_Weapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASTU_Weapon::MakeShot()
{
	FVector PlayerViewLocation;
	FVector PlayerViewDirection;
	GetPlayerViewPoint(PlayerViewLocation, PlayerViewDirection);

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(PlayerViewLocation, PlayerViewDirection, TraceStart, TraceEnd);

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

	if (HitResult.bBlockingHit)
	{
		TraceEnd = HitResult.ImpactPoint;
	}
	ProcessShot(WeaponViewLocation, TraceEnd, HitResult);
}

void ASTU_Weapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	const auto DebugColor = HitResult.bBlockingHit ? FColor::Red : FColor::Blue;
	DrawDebugLine(GetWorld(), ShotStart, ShotEnd, DebugColor, false, 5.0f);
	DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, DebugColor, false, 5.0f);
}

void ASTU_Weapon::GetPlayerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	const auto PlayerController = Character->GetController<APlayerController>();
	if (!PlayerController)
		return;

	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(OutViewLocation, ViewRotation);
	OutViewDirection = ViewRotation.Vector();
}

void ASTU_Weapon::GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const FTransform MuzzleFlashSocketTransform = WeaponMesh->GetSocketTransform(MuzzleFlashSocketName);
	OutViewLocation = MuzzleFlashSocketTransform.GetLocation();
	OutViewDirection = MuzzleFlashSocketTransform.GetRotation().GetForwardVector();
}

void ASTU_Weapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
