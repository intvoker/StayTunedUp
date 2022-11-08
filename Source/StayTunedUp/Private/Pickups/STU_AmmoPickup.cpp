// Stay Tuned Up Game


#include "Pickups/STU_AmmoPickup.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Player/STU_Character.h"

bool ASTU_AmmoPickup::TryUsePickup(ASTU_Character* STU_Character)
{
	if (!STU_Character)
		return false;

	const auto HealthComponent = STU_Character->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return false;

	const auto WeaponComponent = STU_Character->FindComponentByClass<USTU_WeaponComponent>();
	if (!WeaponComponent)
		return false;

	return WeaponComponent->TryAddClip(WeaponClass, ClipAmount);
}
