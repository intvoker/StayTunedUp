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
	int32 NumberOfPlayers = 4;
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

private:
	void SpawnAIControllers();

	APlayerStart* FindPlayerStartByTag(FName PlayerStartTagParam) const;
};
