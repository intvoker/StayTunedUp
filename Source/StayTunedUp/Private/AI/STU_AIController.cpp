// Stay Tuned Up Game


#include "AI/STU_AIController.h"

#include "AI/STU_AICharacter.h"
#include "Components/STU_AIPerceptionComponent.h"

ASTU_AIController::ASTU_AIController()
{
	STU_AIPerceptionComponent = CreateDefaultSubobject<USTU_AIPerceptionComponent>("STU_AIPerceptionComponent");

	SetPerceptionComponent(*STU_AIPerceptionComponent);
}

void ASTU_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto NearestActor = STU_AIPerceptionComponent->FindNearestAliveActor();
	SetFocus(NearestActor);
}

void ASTU_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto STU_AICharacter = Cast<ASTU_AICharacter>(InPawn))
	{
		RunBehaviorTree(STU_AICharacter->BehaviorTree);
	}
}
