// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STU_GameModeBase.generated.h"

class AAIController;
class APlayerStart;

USTRUCT(BlueprintType)
struct FSTU_GameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "64"))
	int32 NumberOfAIPlayers = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
	int32 NumberOfRounds = 2;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ClampMin = "1", ClampMax = "600"))
	int32 SecondsInRound = 30;

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

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

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
	int32 CurrentRoundIndex = 1;
	int32 CurrentRoundRemainingSeconds = 0;
	FTimerHandle UpdateRoundTimerHandle;

	void SpawnAIControllers();

	APlayerStart* FindPlayerStartByTag(FName PlayerStartTagParam) const;

	void StartRound();
	void UpdateRound();

	void RestartPlayers();

	void SetTeams();
	void SetPlayerColor(AController* Controller);
};
