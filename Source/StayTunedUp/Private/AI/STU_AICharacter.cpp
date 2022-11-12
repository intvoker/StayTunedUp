// Stay Tuned Up Game


#include "AI/STU_AICharacter.h"

#include "AI/STU_AIController.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTU_AIController::StaticClass();
}
