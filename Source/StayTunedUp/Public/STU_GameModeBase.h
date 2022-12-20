// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STU_Types.h"
#include "STU_GameModeBase.generated.h"

class AAIController;
class APlayerStart;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameMatchStateChangedSignature, ESTU_GameMatchState, GameMatchState);

USTRUCT(BlueprintType)
struct FSTU_GameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "64"))
	int32 NumberOfAIPlayers = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 NumberOfRounds = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "600"))
	int32 RoundTime = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 RespawnTime = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FLinearColor DefaultTeamColor = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TMap<int32, FLinearColor> TeamsMap;
};

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTU_GameModeBase();

	FGameMatchStateChangedSignature OnGameMatchStateChanged;

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

	bool AreEnemies(const AController* Left, const AController* Right) const;

	void Killed(const AController* Killer, const AController* Victim) const;

	void DoRespawn(AController* Controller);

	int32 GetCurrentRoundIndex() const { return CurrentRoundIndex; }
	int32 GetNumberOfRounds() const { return GameData.NumberOfRounds; }
	int32 GetCurrentRoundRemainingSeconds() const { return CurrentRoundRemainingSeconds; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FSTU_GameData GameData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float UpdateRoundTime = 1.0f;

private:
	ESTU_GameMatchState GameMatchState = ESTU_GameMatchState::None;

	int32 CurrentRoundIndex = 1;
	int32 CurrentRoundRemainingSeconds = 0;
	FTimerHandle UpdateRoundTimerHandle;

	void SetGameMatchState(ESTU_GameMatchState GameMatchStateParam);

	void SpawnAIControllers();

	APlayerStart* FindPlayerStartByTag(const FName& PlayerStartTagParam) const;

	void StartRound();
	void UpdateRound();

	void InitiateRespawn(const AController* Controller) const;

	void RestartPlayers();
	void RestartOnePlayer(AController* Controller);

	void SetTeams();
	void SetPlayerColor(const AController* Controller) const;

	void GameOver();

	void LogPlayers() const;
};
