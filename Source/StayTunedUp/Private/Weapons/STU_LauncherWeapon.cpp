// Stay Tuned Up Game


#include "Weapons/STU_LauncherWeapon.h"

#include "Weapons/STU_Projectile.h"

void ASTU_LauncherWeapon::ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult)
{
	Super::ProcessShot(TraceStart, TraceEnd, HitResult);

	FVector ProjectileDirection = (TraceEnd - TraceStart).GetSafeNormal();
	FTransform ProjectileTransform = FTransform(ProjectileDirection.Rotation(), TraceStart);

	if (const auto Projectile = GetWorld()->SpawnActorDeferred<ASTU_Projectile>(ProjectileClass, ProjectileTransform))
	{
		Projectile->SetProjectileDirection(ProjectileDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(ProjectileTransform);
	}
}
