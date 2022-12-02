// Stay Tuned Up Game


#include "AI/EQS/STU_AmmoPickupEnvQueryTest.h"

#include "Pickups/STU_AmmoPickup.h"
#include "Weapons/STU_Weapon.h"

bool USTU_AmmoPickupEnvQueryTest::CanPickup(AActor* ItemActor) const
{
	const auto STU_AmmoPickup = Cast<ASTU_AmmoPickup>(ItemActor);
	if (!STU_AmmoPickup)
		return false;

	return Super::CanPickup(ItemActor) && STU_AmmoPickup->GetWeaponClass()->IsChildOf(WeaponClass);
}
