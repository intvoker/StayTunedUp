// Stay Tuned Up Game


#include "AI/Services/STU_FindEnemyBTService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STU_AIPerceptionComponent.h"
#include "Components/STU_HealthComponent.h"

USTU_FindEnemyBTService::USTU_FindEnemyBTService()
{
	NodeName = "Find Enemy";
}

void USTU_FindEnemyBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//UE_LOG(LogTemp, Warning, TEXT("FindEnemy TickNode %f"), UGameplayStatics::GetRealTimeSeconds(GetWorld()));

	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return;

	const auto STU_AIPerceptionComponent = AIController->FindComponentByClass<USTU_AIPerceptionComponent>();
	if (!STU_AIPerceptionComponent)
		return;

	const auto EnemyActor = STU_AIPerceptionComponent->FindNearestAliveEnemyActor();
	if (EnemyActor)
	{
		BlackboardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, EnemyActor);
		return;
	}

	const auto CurrentEnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	if (!CurrentEnemyActor)
		return;

	const auto CurrentEnemyActorHealthComponent = CurrentEnemyActor->FindComponentByClass<USTU_HealthComponent>();
	if (!CurrentEnemyActorHealthComponent || CurrentEnemyActorHealthComponent->IsDead())
	{
		BlackboardComponent->ClearValue(EnemyActorKey.SelectedKeyName);
	}
}
