// Stay Tuned Up Game


#include "AI/Decorators/STU_AmmoPercentBTDecorator.h"

#include "AIController.h"
#include "Components/STU_WeaponComponent.h"

USTU_AmmoPercentBTDecorator::USTU_AmmoPercentBTDecorator()
{
	NodeName = "Ammo Percent";
}

bool USTU_AmmoPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return false;

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
		return false;

	const auto WeaponComponent = Pawn->FindComponentByClass<USTU_WeaponComponent>();
	if (!WeaponComponent)
		return false;

	//UE_LOG(LogTemp, Warning, TEXT("Character: %s. AmmoPercent: %f."), *Pawn->GetName(), WeaponComponent->GetWeaponAmmoPercent(WeaponClass));

	return WeaponComponent->GetWeaponAmmoPercent(WeaponClass) < AmmoPercent;
}
