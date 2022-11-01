// Stay Tuned Up Game


#include "Pickups/STU_HealthPickup.h"

#include "Components/STU_HealthComponent.h"
#include "Player/STU_Character.h"

bool ASTU_HealthPickup::TryUsePickup(ASTU_Character* STU_Character)
{
	if (!STU_Character)
		return false;

	const auto HealthComponent = STU_Character->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return false;

	return HealthComponent->TryAddHealth(HealthAmount);
}
