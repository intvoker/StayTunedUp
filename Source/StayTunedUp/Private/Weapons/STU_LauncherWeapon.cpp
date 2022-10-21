// Stay Tuned Up Game


#include "Weapons/STU_LauncherWeapon.h"

#include "Weapons/STU_Projectile.h"

void ASTU_LauncherWeapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	Super::ProcessShot(ShotStart, ShotEnd, HitResult);

	FVector ProjectileDirection = (ShotEnd - ShotStart).GetSafeNormal();
	FTransform ProjectileTransform = FTransform(ProjectileDirection.Rotation(), ShotStart);

	if (const auto Projectile = GetWorld()->SpawnActorDeferred<ASTU_Projectile>(ProjectileClass, ProjectileTransform))
	{
		Projectile->SetProjectileDirection(ProjectileDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(ProjectileTransform);
	}
}
