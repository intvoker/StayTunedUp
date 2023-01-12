// Stay Tuned Up Game


#include "STU_GameModeBase.h"

#include "AIController.h"
#include "Components/STU_RespawnComponent.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"
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

	bStartPlayersAsSpectators = true;
}

void ASTU_GameModeBase::StartPlay()
{
	Super::StartPlay();

	SetOnlySpectator();

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

AActor* ASTU_GameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	//const auto PlayerStateLog = GetPlayerState(Player);
	//UE_LOG(LogTemp, Warning, TEXT("Name: %s. Team ID: %d."), *PlayerStateLog->GetName(), PlayerStateLog->GetTeamID());

	auto FoundPlayerStart = FindPlayerStartByTag(FName(Player->GetName()));
	if (FoundPlayerStart)
	{
		return FoundPlayerStart;
	}

	FoundPlayerStart = FindPlayerStartForController(Player);
	if (FoundPlayerStart)
	{
		FoundPlayerStart->PlayerStartTag = FName(Player->GetName());
		return FoundPlayerStart;
	}

	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

bool ASTU_GameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (GameMatchState != ESTU_GameMatchState::Started)
		return false;

	const auto bPauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if (bPauseSet)
	{
		SetGameMatchState(ESTU_GameMatchState::Paused);
	}

	return bPauseSet;
}

bool ASTU_GameModeBase::ClearPause()
{
	if (GameMatchState != ESTU_GameMatchState::Paused)
		return false;

	const auto bPauseCleared = Super::ClearPause();

	if (bPauseCleared)
	{
		SetGameMatchState(ESTU_GameMatchState::Started);
	}

	return bPauseCleared;
}

bool ASTU_GameModeBase::CanDamage(const AController* Killer, const AController* Victim) const
{
	if (!Killer || !Victim || Killer == Victim)
		return true;

	const auto KillerPlayerState = GetPlayerState(Killer);
	const auto VictimPlayerState = GetPlayerState(Victim);

	return CanDamageTeam(KillerPlayerState, VictimPlayerState);
}

bool ASTU_GameModeBase::CanKill(const AController* Killer, const AController* Victim) const
{
	const auto KillerPlayerState = GetPlayerState(Killer);
	const auto VictimPlayerState = GetPlayerState(Victim);

	return CanKillTeam(KillerPlayerState, VictimPlayerState);
}

void ASTU_GameModeBase::Killed(const AController* Killer, const AController* Victim) const
{
	//const auto KillerString = FString::Printf(TEXT("%s"), Killer ? *Killer->GetName() : TEXT("nullptr"));
	//const auto VictimString = FString::Printf(TEXT("%s"), Victim ? *Victim->GetName() : TEXT("nullptr"));
	//UE_LOG(LogTemp, Warning, TEXT("Killer: %s. Victim: %s."), *KillerString, *VictimString);

	const auto KillerPlayerState = GetPlayerState(Killer);
	const auto VictimPlayerState = GetPlayerState(Victim);

	if (KillerPlayerState && VictimPlayerState)
	{
		if (CanKillTeam(KillerPlayerState, VictimPlayerState))
		{
			KillerPlayerState->AddKill();
		}
		else
		{
			KillerPlayerState->AddFriendlyKill();
		}

		if (CanSetTeam(KillerPlayerState, VictimPlayerState))
		{
			SetPlayerTeam(Victim, KillerPlayerState->GetTeamID());
		}
	}

	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}

	InitiateRespawn(Victim);
}

void ASTU_GameModeBase::DoRespawn(AController* Controller)
{
	RestartOnePlayer(Controller);
}

TArray<ASTU_PlayerState*> ASTU_GameModeBase::GetPlayerStates() const
{
	TArray<ASTU_PlayerState*> PlayerStates;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto PlayerState = GetPlayerState(It->Get());
		if (!PlayerState)
			continue;

		PlayerStates.Add(PlayerState);
	}

	return PlayerStates;
}

ASTU_PlayerState* ASTU_GameModeBase::GetPlayerState(const AController* Controller) const
{
	if (!Controller)
		return nullptr;

	return Cast<ASTU_PlayerState>(Controller->PlayerState);
}

void ASTU_GameModeBase::SetOnlySpectator() const
{
	if (!GameData.bPlayerIsOnlySpectator)
		return;

	if (const auto PlayerController = GEngine->GetFirstLocalPlayerController(GetWorld()))
	{
		if (const auto PlayerState = PlayerController->PlayerState)
		{
			PlayerState->SetIsOnlyASpectator(true);
		}
	}
}

void ASTU_GameModeBase::SetGameMatchState(ESTU_GameMatchState GameMatchStateParam)
{
	if (GameMatchState == GameMatchStateParam)
		return;

	GameMatchState = GameMatchStateParam;

	OnGameMatchStateChanged.Broadcast(GameMatchState);
}

void ASTU_GameModeBase::SpawnAIControllers() const
{
	for (auto _ = GameData.NumberOfAIPlayers; _--;)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
	}
}

APlayerStart* ASTU_GameModeBase::FindPlayerStartForController(const AController* Controller) const
{
	auto PlayerStart = FindPlayerStartByTag(StartTagForController(Controller));

	if (!PlayerStart)
	{
		if (const auto PlayerState = GetPlayerState(Controller))
		{
			PlayerStart = FindPlayerStartByTag(FName(FString::FromInt(PlayerState->GetTeamID())));
		}
	}

	return PlayerStart;
}

FName ASTU_GameModeBase::StartTagForController(const AController* Controller) const
{
	FName StartTag = NAME_None;

	if (const auto STU_PlayerController = Cast<ASTU_PlayerController>(Controller))
	{
		if (!GameData.bPlayerIsOnlySpectator)
		{
			StartTag = STU_PlayerController->PlayerStartTag;
		}
		else
		{
			StartTag = STU_PlayerController->SpectatorStartTag;
		}
	}

	return StartTag;
}

APlayerStart* ASTU_GameModeBase::FindPlayerStartByTag(const FName& PlayerStartTagParam) const
{
	if (PlayerStartTagParam.IsNone())
		return nullptr;

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart->PlayerStartTag == PlayerStartTagParam)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Using Tag: %s Found PlayerStart: %s."), *PlayerStartTagParam.ToString(), *UKismetSystemLibrary::GetDisplayName(PlayerStart));
			return PlayerStart;
		}
	}

	return nullptr;
}

void ASTU_GameModeBase::StartRound()
{
	RestartPlayers();

	CurrentRoundRemainingSeconds = GameData.RoundTime;

	if (GameData.bNoTimeLimit)
		return;

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

void ASTU_GameModeBase::SetTeams() const
{
	int32 CurrentTeamID = 1;
	int32 CurrentPlayerIndex = 1;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();

		SetPlayerTeam(Controller, CurrentTeamID);
		SetPlayerName(Controller, CurrentPlayerIndex);

		CurrentTeamID = GetNextTeamID(CurrentTeamID);
		CurrentPlayerIndex++;
	}
}

void ASTU_GameModeBase::SetPlayerTeam(const AController* Controller, int32 TeamID) const
{
	const auto PlayerState = GetPlayerState(Controller);
	if (!PlayerState)
		return;

	if (!GameData.TeamsMap.Contains(TeamID))
		return;

	PlayerState->SetTeamID(TeamID);
	PlayerState->SetTeamColor(GameData.TeamsMap[TeamID]);
}

void ASTU_GameModeBase::SetPlayerName(const AController* Controller, int32 PlayerIndex) const
{
	const auto PlayerState = GetPlayerState(Controller);
	if (!PlayerState)
		return;

	FString PlayerName;
	if (Cast<APlayerController>(Controller))
	{
		PlayerName = FString::Printf(TEXT("Player %d"), PlayerIndex);
	}
	else
	{
		PlayerName = FString::Printf(TEXT("Bot %d"), PlayerIndex);
	}

	PlayerState->SetPlayerName(PlayerName);
}

void ASTU_GameModeBase::SetPlayerColor(const AController* Controller) const
{
	if (!Controller)
		return;

	const auto STU_Character = Cast<ASTU_Character>(Controller->GetPawn());
	if (!STU_Character)
		return;

	const auto PlayerState = GetPlayerState(Controller);
	if (!PlayerState)
		return;

	STU_Character->SetPlayerColor(PlayerState->GetTeamColor());
}

int32 ASTU_GameModeBase::GetNextTeamID(const int32 TeamID) const
{
	const int32 NumberOfTeams = GameData.TeamsMap.Num();

	const int32 NextTeamID = TeamID >= NumberOfTeams ? 1 : TeamID + 1;

	return NextTeamID;
}

bool ASTU_GameModeBase::CanDamageTeam(const ASTU_PlayerState* KillerPlayerState,
                                      const ASTU_PlayerState* VictimPlayerState) const
{
	if (!KillerPlayerState || !VictimPlayerState)
		return false;

	if (KillerPlayerState->GetTeamID() == VictimPlayerState->GetTeamID())
		return GameData.bAllowFriendlyFire;

	return CanKillTeam(KillerPlayerState, VictimPlayerState);
}

bool ASTU_GameModeBase::CanKillTeam(const ASTU_PlayerState* KillerPlayerState,
                                    const ASTU_PlayerState* VictimPlayerState) const
{
	if (!KillerPlayerState || !VictimPlayerState)
		return false;

	switch (GameData.GameRules)
	{
	case ESTU_GameRules::TDM:
		return KillerPlayerState->GetTeamID() != VictimPlayerState->GetTeamID();
	case ESTU_GameRules::RPS:
		return GetNextTeamID(KillerPlayerState->GetTeamID()) == VictimPlayerState->GetTeamID();
	default:
		return false;
	}
}

bool ASTU_GameModeBase::CanSetTeam(const ASTU_PlayerState* KillerPlayerState,
                                   const ASTU_PlayerState* VictimPlayerState) const
{
	if (!KillerPlayerState || !VictimPlayerState)
		return false;

	switch (GameData.GameRules)
	{
	case ESTU_GameRules::TDM:
		return false;
	case ESTU_GameRules::RPS:
		return true;
	default:
		return false;
	}
}

void ASTU_GameModeBase::GameOver()
{
	for (const auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		Pawn->TurnOff();
		Pawn->DisableInput(nullptr);
	}

	SetGameMatchState(ESTU_GameMatchState::Finished);
}
