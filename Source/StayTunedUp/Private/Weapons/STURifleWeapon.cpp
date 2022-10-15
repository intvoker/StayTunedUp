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

void ASTURifleWeapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	Direction = FMath::VRandCone(Direction, FMath::DegreesToRadians(ShotSpread));
	
	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
