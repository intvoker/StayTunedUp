// Stay Tuned Up Game


#include "AI/EQS/STU_EnemyActorEnvQueryContext.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTU_EnemyActorEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance,
                                                    FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	const auto QueryOwner = Cast<APawn>(QueryInstance.Owner.Get());
	if (!QueryOwner)
		return;

	const auto AIController = QueryOwner->GetController<AAIController>();
	if (!AIController)
		return;

	const auto BlackboardComponent = AIController->GetBlackboardComponent();
	if (!BlackboardComponent)
		return;
	
	const auto EnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKeyName));
	if (!EnemyActor)
		return;
	
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, EnemyActor);
}
