// Stay Tuned Up Game


#include "STU_MenuGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/STU_MenuPlayerController.h"
#include "UI/STU_MenuHUD.h"

ASTU_MenuGameModeBase::ASTU_MenuGameModeBase()
{
	PlayerControllerClass = ASTU_MenuPlayerController::StaticClass();
	HUDClass = ASTU_MenuHUD::StaticClass();
}

void ASTU_MenuGameModeBase::StartLevel(FName LevelName) const
{
	UGameplayStatics::OpenLevel(this, LevelName);
}
