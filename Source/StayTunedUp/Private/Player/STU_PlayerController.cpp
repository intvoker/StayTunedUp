// Stay Tuned Up Game


#include "Player/STU_PlayerController.h"

#include "Components/STU_RespawnComponent.h"
#include "GameFramework/SpectatorPawn.h"

ASTU_PlayerController::ASTU_PlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");
}

void ASTU_PlayerController::SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn)
{
	Super::SetSpectatorPawn(NewSpectatorPawn);

	if (NewSpectatorPawn)
	{
		NewSpectatorPawn->bUseControllerRotationPitch = true;
		NewSpectatorPawn->bUseControllerRotationYaw = true;
	}
}
