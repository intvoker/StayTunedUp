// Stay Tuned Up Game


#include "AI/Tasks/STU_FindRandomLocationBTTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

USTU_FindRandomLocationBTTask::USTU_FindRandomLocationBTTask()
{
	NodeName = "Find Random Location";
}

EBTNodeResult::Type USTU_FindRandomLocationBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return EBTNodeResult::Failed;

	const auto CenterActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(CenterActorKey.SelectedKeyName));
	if (!CenterActor)
		return EBTNodeResult::Failed;

	const auto NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavigationSystem)
		return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	const auto bSuccess = NavigationSystem->
		GetRandomReachablePointInRadius(CenterActor->GetActorLocation(), Radius, NavLocation);
	if (!bSuccess)
		return EBTNodeResult::Failed;

	BlackboardComponent->SetValueAsVector(RandomLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}
