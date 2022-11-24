// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "AI/EQS/STU_PickupEnvQueryTest.h"
#include "STU_AmmoPickupEnvQueryTest.generated.h"

class ASTU_Weapon;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_AmmoPickupEnvQueryTest : public USTU_PickupEnvQueryTest
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ASTU_Weapon> WeaponClass;

	virtual bool CanPickup(AActor* ItemActor) const override;
};
