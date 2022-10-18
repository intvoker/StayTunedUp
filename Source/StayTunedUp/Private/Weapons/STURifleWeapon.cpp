// Stay Tuned Up Game


#include "Weapons/STURifleWeapon.h"

void ASTURifleWeapon::Fire()
{
	MakeShot();

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
}

void ASTURifleWeapon::StopFiring()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTURifleWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTURifleWeapon::ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult)
{
	const auto DebugColor = HitResult.bBlockingHit ? FColor::Red : FColor::Blue;

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, DebugColor, false, 5.0f);
	DrawDebugSphere(GetWorld(), TraceEnd, 10.0f, 24, DebugColor, false, 5.0f);

	DealDamage(HitResult);
}

void ASTURifleWeapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(ShotSpread));

	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
