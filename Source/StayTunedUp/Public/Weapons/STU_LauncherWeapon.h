// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STU_Weapon.h"
#include "STU_LauncherWeapon.generated.h"

class ASTU_Projectile;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_LauncherWeapon : public ASTU_Weapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTU_Projectile> ProjectileClass;

	virtual void ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult) override;
};
