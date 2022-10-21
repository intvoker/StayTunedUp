// Stay Tuned Up Game


#include "STU_GameModeBase.h"

#include "Player/STU_Character.h"
#include "Player/STU_PlayerController.h"
#include "UI/STU_HUD.h"

ASTU_GameModeBase::ASTU_GameModeBase()
{
	DefaultPawnClass = ASTU_Character::StaticClass();
	PlayerControllerClass = ASTU_PlayerController::StaticClass();
	HUDClass = ASTU_HUD::StaticClass();
}
