// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STUBaseWeapon.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;
/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTULauncherWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUProjectile> ProjectileClass;

	virtual void ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult) override;
};
