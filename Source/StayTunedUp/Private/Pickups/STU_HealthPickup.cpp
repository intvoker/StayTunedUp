// Stay Tuned Up Game


#include "Pickups/STU_HealthPickup.h"

#include "Components/STU_HealthComponent.h"
#include "GameFramework/Character.h"

bool ASTU_HealthPickup::TryUsePickup(ACharacter* Character)
{
	if (!Character)
		return false;

	const auto HealthComponent = Character->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return false;

	return HealthComponent->TryAddHealth(HealthAmount);
}
