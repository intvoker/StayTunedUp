// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_PlayerController.generated.h"

class USTU_RespawnComponent;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTU_PlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_RespawnComponent* RespawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName PlayerStartTag;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn) override;

private:
	bool bPaused = false;

	void PausePressed();

	UFUNCTION()
	void OnGameMatchStateChanged(ESTU_GameMatchState GameMatchState);
};
