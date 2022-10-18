// Stay Tuned Up Game


#include "Weapons/STULauncherWeapon.h"

#include "Weapons/STUProjectile.h"

void ASTULauncherWeapon::Fire()
{
	MakeShot();
}

void ASTULauncherWeapon::StopFiring()
{
}

void ASTULauncherWeapon::ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult)
{
	FTransform ProjectileTransform = FTransform(FRotator::ZeroRotator, TraceStart);

	auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, ProjectileTransform);
	if (Projectile)
	{
		Projectile->FinishSpawning(ProjectileTransform);
	}
}
