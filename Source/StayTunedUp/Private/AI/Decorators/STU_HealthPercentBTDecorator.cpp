// Stay Tuned Up Game


#include "AI/Decorators/STU_HealthPercentBTDecorator.h"

#include "AIController.h"
#include "Components/STU_HealthComponent.h"

USTU_HealthPercentBTDecorator::USTU_HealthPercentBTDecorator()
{
	NodeName = "Health Percent";
}

bool USTU_HealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                               uint8* NodeMemory) const
{
	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return false;

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
		return false;

	const auto HealthComponent = Pawn->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return false;

	return HealthComponent->GetHealthPercent() <= HealthPercent;
}
