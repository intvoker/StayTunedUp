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

public:
	virtual bool CanUsePickup(ASTU_Character* STU_Character) override;

protected:
	virtual void UsePickup(ASTU_Character* STU_Character) override;
};
