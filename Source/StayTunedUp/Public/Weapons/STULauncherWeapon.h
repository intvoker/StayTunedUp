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

public:
	virtual void Fire() override;
	virtual void StopFiring() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUProjectile> ProjectileClass;

	virtual void ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult) override;
};
