// Stay Tuned Up Game


#include "AI/EQS/STU_AmmoPickupEnvQueryTest.h"

#include "Pickups/STU_AmmoPickup.h"
#include "Weapons/STU_Weapon.h"

template <typename T>
bool CompareTSubclassOf(TSubclassOf<T> Left, TSubclassOf<T> Right)
{
	return Left->IsChildOf(Right) || Right->IsChildOf(Left);
}

bool USTU_AmmoPickupEnvQueryTest::CanPickup(AActor* ItemActor) const
{
	const auto STU_AmmoPickup = Cast<ASTU_AmmoPickup>(ItemActor);
	if (!STU_AmmoPickup)
		return false;

	return Super::CanPickup(ItemActor) && STU_AmmoPickup->GetWeaponClass()->IsChildOf(WeaponClass);
}
