// Stay Tuned Up Game


#include "Weapons/STU_RifleWeapon.h"

#include "Components/STU_WeaponEffectsComponent.h"

void ASTU_RifleWeapon::Fire()
{
	GetWorld()->GetTimerManager().SetTimer(MakeShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);

	Super::Fire();
}

void ASTU_RifleWeapon::StopFiring()
{
	GetWorld()->GetTimerManager().ClearTimer(MakeShotTimerHandle);

	Super::StopFiring();
}

void ASTU_RifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTU_RifleWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(MakeShotTimerHandle);
}

void ASTU_RifleWeapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	Super::ProcessShot(ShotStart, ShotEnd, HitResult);

	if (HitResult.bBlockingHit)
	{
		WeaponEffectsComponent->SpawnImpactEffect(HitResult);
	}
	else
	{
		//const FVector ShotDirection = (ShotEnd - ShotStart).GetSafeNormal();
		//WeaponEffectsComponent->SpawnNoImpactEffect(ShotEnd, ShotDirection.Rotation().GetInverse());
	}

	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
		return;

	const auto Controller = GetOwner() ? GetOwner()->GetInstigatorController() : nullptr;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), Controller, GetOwner());
}

void ASTU_RifleWeapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	//return Super::GetTraceData(Location, Direction, OutTraceStart, OutTraceEnd);

	Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(ShotSpread));

	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
