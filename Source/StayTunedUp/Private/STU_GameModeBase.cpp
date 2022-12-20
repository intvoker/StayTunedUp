// Stay Tuned Up Game


#include "STU_GameModeBase.h"

#include "AIController.h"
#include "Components/STU_RespawnComponent.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STU_Character.h"
#include "Player/STU_PlayerCharacter.h"
#include "Player/STU_PlayerController.h"
#include "Player/STU_PlayerState.h"
#include "UI/STU_HUD.h"

ASTU_GameModeBase::ASTU_GameModeBase()
{
	PlayerControllerClass = ASTU_PlayerController::StaticClass();
	PlayerStateClass = ASTU_PlayerState::StaticClass();
	HUDClass = ASTU_HUD::StaticClass();
	DefaultPawnClass = ASTU_PlayerCharacter::StaticClass();
}

void ASTU_GameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnAIControllers();
	SetTeams();

	StartRound();

	SetGameMatchState(ESTU_GameMatchState::Started);
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

bool ASTU_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto bPauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if (bPauseSet)
	{
		SetGameMatchState(ESTU_GameMatchState::Paused);
	}

	return bPauseSet;
}

bool ASTU_GameModeBase::ClearPause()
{
	const auto bPauseCleared = Super::ClearPause();

	if (bPauseCleared)
	{
		SetGameMatchState(ESTU_GameMatchState::Started);
	}

	return bPauseCleared;
}

bool ASTU_GameModeBase::AreEnemies(const AController* Left, const AController* Right) const
{
	if (!Left || !Right || Left == Right)
		return false;

	const auto STU_PlayerStateLeft = Cast<ASTU_PlayerState>(Left->PlayerState);
	const auto STU_PlayerStateRight = Cast<ASTU_PlayerState>(Right->PlayerState);

	if (!STU_PlayerStateLeft || !STU_PlayerStateRight)
		return false;

	return STU_PlayerStateLeft->GetTeamID() != STU_PlayerStateRight->GetTeamID();
}

void ASTU_GameModeBase::Killed(const AController* Killer, const AController* Victim) const
{
	if (!Killer || !Victim)
		return;

	const auto STU_PlayerStateKiller = Cast<ASTU_PlayerState>(Killer->PlayerState);
	const auto STU_PlayerStateVictim = Cast<ASTU_PlayerState>(Victim->PlayerState);

	if (STU_PlayerStateKiller)
	{
		if (AreEnemies(Killer, Victim))
		{
			STU_PlayerStateKiller->AddKill();
		}
		else
		{
			STU_PlayerStateKiller->AddFriendlyKill();
		}
	}

	if (STU_PlayerStateVictim)
	{
		STU_PlayerStateVictim->AddDeath();
	}

	InitiateRespawn(Victim);
}

void ASTU_GameModeBase::DoRespawn(AController* Controller)
{
	RestartOnePlayer(Controller);
}

void ASTU_GameModeBase::RestartCurrentLevel() const
{
	const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void ASTU_GameModeBase::SetGameMatchState(ESTU_GameMatchState GameMatchStateParam)
{
	if (GameMatchState == GameMatchStateParam)
		return;

	GameMatchState = GameMatchStateParam;

	OnGameMatchStateChanged.Broadcast(GameMatchState);
}

void ASTU_GameModeBase::SpawnAIControllers()
{
	for (auto _ = GameData.NumberOfAIPlayers; _--;)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}
}

APlayerStart* ASTU_GameModeBase::FindPlayerStartByTag(const FName& PlayerStartTagParam) const
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

void ASTU_GameModeBase::StartRound()
{
	CurrentRoundRemainingSeconds = GameData.RoundTime;
	GetWorld()->GetTimerManager().SetTimer(UpdateRoundTimerHandle, this, &ThisClass::UpdateRound, UpdateRoundTime,
	                                       true);
}

void ASTU_GameModeBase::UpdateRound()
{
	CurrentRoundRemainingSeconds -= UpdateRoundTime;

	if (CurrentRoundRemainingSeconds <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateRoundTimerHandle);

		if (CurrentRoundIndex < GameData.NumberOfRounds)
		{
			CurrentRoundIndex++;

			RestartPlayers();
			StartRound();
		}
		else
		{
			GameOver();
		}
	}
}

void ASTU_GameModeBase::InitiateRespawn(const AController* Controller) const
{
	if (CurrentRoundRemainingSeconds <= GameData.RespawnTime + UpdateRoundTime)
		return;

	if (!Controller)
		return;

	const auto RespawnComponent = Controller->FindComponentByClass<USTU_RespawnComponent>();
	if (!RespawnComponent)
		return;

	RespawnComponent->StartRespawn(GameData.RespawnTime);
}

void ASTU_GameModeBase::RestartPlayers()
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		RestartOnePlayer(Controller);
	}
}

void ASTU_GameModeBase::RestartOnePlayer(AController* Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void ASTU_GameModeBase::SetTeams()
{
	int32 CurrentTeamID = 1;
	const int32 NumberOfTeams = GameData.TeamsMap.Num();

	if (!NumberOfTeams)
		return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
			continue;

		const auto STU_PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!STU_PlayerState)
			continue;

		STU_PlayerState->SetTeamID(CurrentTeamID);
		STU_PlayerState->SetTeamColor(GameData.TeamsMap[CurrentTeamID]);
		SetPlayerColor(Controller);

		CurrentTeamID++;
		if (CurrentTeamID > NumberOfTeams)
		{
			CurrentTeamID = 1;
		}
	}
}

void ASTU_GameModeBase::SetPlayerColor(const AController* Controller) const
{
	if (!Controller)
		return;

	const auto STU_Character = Cast<ASTU_Character>(Controller->GetPawn());
	if (!STU_Character)
		return;

	const auto STU_PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
	if (!STU_PlayerState)
		return;

	STU_Character->SetPlayerColor(STU_PlayerState->GetTeamColor());
}

void ASTU_GameModeBase::GameOver()
{
	LogPlayers();

	for (const auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		Pawn->TurnOff();
		Pawn->DisableInput(nullptr);
	}

	SetGameMatchState(ESTU_GameMatchState::Finished);
}

void ASTU_GameModeBase::LogPlayers() const
{
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller)
			continue;

		const auto STU_PlayerState = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!STU_PlayerState)
			continue;

		UE_LOG(LogTemp, Warning, TEXT("Player: %s. Info: %s."), *Controller->GetName(),
		       *STU_PlayerState->GetPlayerStateInfo());
	}
}
