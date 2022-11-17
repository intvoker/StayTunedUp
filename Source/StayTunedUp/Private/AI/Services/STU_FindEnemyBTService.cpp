// Stay Tuned Up Game


#include "AI/Services/STU_FindEnemyBTService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STU_AIPerceptionComponent.h"

USTU_FindEnemyBTService::USTU_FindEnemyBTService()
{
	NodeName = "Find Enemy";
}

void USTU_FindEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return;

	const auto STU_AIPerceptionComponent = AIController->FindComponentByClass<USTU_AIPerceptionComponent>();
	if (!STU_AIPerceptionComponent)
		return;

	BlackboardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName,
	                                      STU_AIPerceptionComponent->FindNearestAliveActor());
}
