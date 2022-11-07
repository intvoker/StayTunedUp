// Stay Tuned Up Game


#include "Weapons/STU_RifleWeapon.h"

#include "Components/STU_WeaponEffectsComponent.h"

void ASTU_RifleWeapon::Fire()
{
	Super::Fire();

	GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
}

void ASTU_RifleWeapon::StopFiring()
{
	Super::StopFiring();

	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTU_RifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTU_RifleWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTU_RifleWeapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	Super::ProcessShot(ShotStart, ShotEnd, HitResult);

	if (HitResult.bBlockingHit)
	{
		WeaponEffectsComponent->SpawnImpactEffect(HitResult);
	}

	const auto DamagedActor = HitResult.GetActor();
	if (!DamagedActor)
		return;

	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetOwner()->GetInstigatorController(), GetOwner());
}

void ASTU_RifleWeapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(ShotSpread));

	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
