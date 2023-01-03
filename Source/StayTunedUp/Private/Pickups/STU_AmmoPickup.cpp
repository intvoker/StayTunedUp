// Stay Tuned Up Game


#include "Pickups/STU_AmmoPickup.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "GameFramework/Character.h"

bool ASTU_AmmoPickup::TryUsePickup(ACharacter* Character)
{
	if (!Character)
		return false;

	const auto HealthComponent = Character->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return false;

	const auto WeaponComponent = Character->FindComponentByClass<USTU_WeaponComponent>();
	if (!WeaponComponent)
		return false;

	return WeaponComponent->TryAddClip(WeaponClass, ClipAmount);
}
