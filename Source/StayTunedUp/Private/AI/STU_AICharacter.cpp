// Stay Tuned Up Game


#include "AI/STU_AICharacter.h"

#include "AI/STU_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTU_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
}
