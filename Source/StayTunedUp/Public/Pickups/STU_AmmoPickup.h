// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STU_Pickup.h"
#include "STU_AmmoPickup.generated.h"

class ASTU_Weapon;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_AmmoPickup : public ASTU_Pickup
{
	GENERATED_BODY()

public:
	TSubclassOf<ASTU_Weapon> GetWeaponClass() const { return WeaponClass; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTU_Weapon> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 ClipAmount = 2;

	virtual bool TryUsePickup(ACharacter* Character) override;
};
