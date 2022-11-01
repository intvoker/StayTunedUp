// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STU_Pickup.h"
#include "STU_HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_HealthPickup : public ASTU_Pickup
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthAmount = 50.0f;

	virtual bool TryUsePickup(ASTU_Character* STU_Character) override;
};
