// Stay Tuned Up Game


#include "AI/UBTTask_STU_FindRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UUBTTask_STU_FindRandomLocation::UUBTTask_STU_FindRandomLocation()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type UUBTTask_STU_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return EBTNodeResult::Failed;

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return EBTNodeResult::Failed;

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
		return EBTNodeResult::Failed;

	const auto NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavigationSystem)
		return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	const auto bSuccess = NavigationSystem->
		GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation);
	if (!bSuccess)
		return EBTNodeResult::Failed;

	BlackboardComponent->SetValueAsVector(RandomLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}
