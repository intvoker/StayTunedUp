// Stay Tuned Up Game


#include "STU_GameModeBase.h"

#include "AIController.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Player/STU_Character.h"
#include "Player/STU_PlayerController.h"
#include "UI/STU_HUD.h"

ASTU_GameModeBase::ASTU_GameModeBase()
{
	DefaultPawnClass = ASTU_Character::StaticClass();
	PlayerControllerClass = ASTU_PlayerController::StaticClass();
	HUDClass = ASTU_HUD::StaticClass();
}

void ASTU_GameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnAIControllers();
}

UClass* ASTU_GameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA(AAIController::StaticClass()))
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* ASTU_GameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (const auto STU_PlayerController = Cast<ASTU_PlayerController>(Player))
	{
		if (!STU_PlayerController->PlayerStartTag.IsNone())
		{
			if (const auto FoundPlayerStart = FindPlayerStartByTag(STU_PlayerController->PlayerStartTag))
				return FoundPlayerStart;
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}

void ASTU_GameModeBase::SpawnAIControllers()
{
	for (auto _ = GameData.NumberOfPlayers; _--;)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

APlayerStart* ASTU_GameModeBase::FindPlayerStartByTag(FName PlayerStartTagParam) const
{
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart->PlayerStartTag == PlayerStartTagParam)
		{
			return PlayerStart;
		}
	}

	return nullptr;
}
