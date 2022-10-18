// Stay Tuned Up Game


#include "Weapons/STULauncherWeapon.h"

#include "Weapons/STUProjectile.h"

void ASTULauncherWeapon::ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult)
{
	Super::ProcessShot(TraceStart, TraceEnd, HitResult);

	FVector ProjectileDirection = (TraceEnd - TraceStart).GetSafeNormal();
	FTransform ProjectileTransform = FTransform(ProjectileDirection.Rotation(), TraceStart);

	if (const auto Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, ProjectileTransform))
	{
		Projectile->SetProjectileDirection(ProjectileDirection);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(ProjectileTransform);
	}
}
