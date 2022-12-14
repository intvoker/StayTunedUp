// Stay Tuned Up Game


#include "Weapons/STU_Weapon.h"

#include "Animations/STU_AnimUtility.h"
#include "Components/STU_EffectComponent.h"
#include "Components/STU_WeaponEffectsComponent.h"
#include "STU_ControllerViewPointInterface.h"

// Sets default values
ASTU_Weapon::ASTU_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	MuzzleEffectComponent = CreateDefaultSubobject<USTU_EffectComponent>("MuzzleEffectComponent");
	MuzzleEffectComponent->SetupEffectAttachment(WeaponMesh, MuzzleFlashSocketName);

	AmmoEmptyEffectComponent = CreateDefaultSubobject<USTU_EffectComponent>("AmmoEmptyEffectComponent");
	AmmoEmptyEffectComponent->SetupEffectAttachment(WeaponMesh, MuzzleFlashSocketName);

	WeaponEffectsComponent = CreateDefaultSubobject<USTU_WeaponEffectsComponent>("WeaponEffectsComponent");
}

void ASTU_Weapon::Fire()
{
	MakeShot();
}

void ASTU_Weapon::StopFiring()
{
	MuzzleEffectComponent->Despawn();
}

bool ASTU_Weapon::CanUseClip() const
{
	return CurrentAmmo.Clips > 0;
}

void ASTU_Weapon::UseClip()
{
	if (!CanUseClip())
		return;

	CurrentAmmo.Rounds = DefaultAmmo.Rounds;

	if (!CurrentAmmo.bInfinite)
	{
		CurrentAmmo.Clips--;
	}
}

bool ASTU_Weapon::IsClipEmpty() const
{
	return !CanUseRound();
}

bool ASTU_Weapon::IsAmmoEmpty() const
{
	return !CanUseClip() && !CanUseRound();
}

bool ASTU_Weapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Rounds == DefaultAmmo.Rounds;
}

float ASTU_Weapon::GetAmmoPercent() const
{
	const float TotalDefaultRounds = DefaultAmmo.Clips * DefaultAmmo.Rounds + DefaultAmmo.Rounds;
	const float TotalCurrentRounds = CurrentAmmo.Clips * DefaultAmmo.Rounds + CurrentAmmo.Rounds;

	if (TotalDefaultRounds == 0.0f)
		return 0.0f;

	return TotalCurrentRounds / TotalDefaultRounds;
}

void ASTU_Weapon::OnOwnerDeath()
{
	STU_AnimUtility::SetRagdoll(this, WeaponMesh);

	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	SetLifeSpan(LifeSpan);
}

bool ASTU_Weapon::TryAddClip(float ClipAmount)
{
	if (CurrentAmmo.bInfinite)
		return false;

	if (IsAmmoFull())
		return false;

	SetClips(CurrentAmmo.Clips + ClipAmount);

	return true;
}

// Called when the game starts or when spawned
void ASTU_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;
}

void ASTU_Weapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASTU_Weapon::MakeShot()
{
	if (!CanUseRound())
	{
		StopFiring();

		if (IsAmmoEmpty())
		{
			AmmoEmptyEffectComponent->Spawn();
		}

		return;
	}

	MuzzleEffectComponent->Spawn();

	FVector ShotViewLocation;
	FVector ShotViewDirection;
	GetShotViewPoint(ShotViewLocation, ShotViewDirection);

	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(ShotViewLocation, ShotViewDirection, TraceStart, TraceEnd);

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

	UseRound();

	if (HitResult.bBlockingHit)
	{
		TraceEnd = HitResult.ImpactPoint;
	}

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	WeaponEffectsComponent->SpawnTraceEffect(WeaponViewLocation, TraceEnd);

	ProcessShot(WeaponViewLocation, TraceEnd, HitResult);
}

void ASTU_Weapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	/*
	const auto DebugColor = HitResult.bBlockingHit ? FColor::Red : FColor::Blue;
	DrawDebugLine(GetWorld(), ShotStart, ShotEnd, DebugColor, false, 5.0f, 0, 2.0f);
	DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, DebugColor, false, 5.0f);
	*/
}

void ASTU_Weapon::GetShotViewPoint(FVector& OutViewLocation, FVector& OutViewDirection) const
{
	FVector ControllerViewLocation;
	FVector ControllerViewDirection;
	GetControllerViewPoint(ControllerViewLocation, ControllerViewDirection);

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	const FVector ControllerToWeapon = WeaponViewLocation - ControllerViewLocation;
	const FVector ControllerToWeaponProjected = ControllerToWeapon.ProjectOnToNormal(ControllerViewDirection);

	OutViewLocation = ControllerViewLocation + ControllerToWeaponProjected;
	OutViewDirection = ControllerViewDirection;
}

void ASTU_Weapon::GetControllerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection) const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
		return;

	const auto Controller = Pawn->GetController();
	if (!Controller)
		return;

	if (const auto ControllerViewPointInterface = Cast<ISTU_ControllerViewPointInterface>(Controller))
	{
		FRotator ViewRotation;
		ControllerViewPointInterface->GetControllerViewPoint(OutViewLocation, ViewRotation);
		OutViewDirection = ViewRotation.Vector();
	}
}

void ASTU_Weapon::GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection) const
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

bool ASTU_Weapon::CanUseRound() const
{
	return CurrentAmmo.Rounds > 0;
}

void ASTU_Weapon::UseRound()
{
	if (!CanUseRound())
		return;

	CurrentAmmo.Rounds--;

	if (!CanUseRound())
	{
		StopFiring();
		OnClipEmpty.Broadcast(this);
	}
}

void ASTU_Weapon::SetClips(float NewClips)
{
	CurrentAmmo.Clips = FMath::Clamp(NewClips, 0.0f, DefaultAmmo.Clips);

	if (NewClips > DefaultAmmo.Clips)
	{
		CurrentAmmo.Rounds = DefaultAmmo.Rounds;
	}

	if (!CanUseRound())
	{
		StopFiring();
		OnClipEmpty.Broadcast(this);
	}
}
