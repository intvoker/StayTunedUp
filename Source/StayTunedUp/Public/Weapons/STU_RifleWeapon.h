// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Weapons/STU_Weapon.h"
#include "STU_RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_RifleWeapon : public ASTU_Weapon
{
	GENERATED_BODY()

public:
	virtual void Fire() override;
	virtual void StopFiring() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ShotSpread = 1.5f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult) override;

	virtual void GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart,
	                          FVector& OutTraceEnd) override;

private:
	FTimerHandle ShotTimerHandle;
};
