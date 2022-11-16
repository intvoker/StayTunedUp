// Stay Tuned Up Game


#include "AI/STU_AIController.h"

#include "AI/STU_AICharacter.h"

void ASTU_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto STU_AICharacter = Cast<ASTU_AICharacter>(InPawn))
	{
		RunBehaviorTree(STU_AICharacter->BehaviorTree);
	}
}
