// Stay Tuned Up Game


#include "Player/STU_MenuPlayerController.h"

void ASTU_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
