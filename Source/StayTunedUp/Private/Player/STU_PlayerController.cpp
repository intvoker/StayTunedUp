// Stay Tuned Up Game


#include "Player/STU_PlayerController.h"

#include "GameFramework/SpectatorPawn.h"

void ASTU_PlayerController::SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn)
{
	Super::SetSpectatorPawn(NewSpectatorPawn);

	if (NewSpectatorPawn)
	{
		NewSpectatorPawn->bUseControllerRotationPitch = true;
		NewSpectatorPawn->bUseControllerRotationYaw = true;
	}
}
