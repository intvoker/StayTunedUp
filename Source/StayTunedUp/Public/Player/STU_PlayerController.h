// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_ControllerViewPointInterface.h"
#include "STU_PlayerController.generated.h"

class USTU_RespawnComponent;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_PlayerController : public APlayerController, public ISTU_ControllerViewPointInterface
{
	GENERATED_BODY()

public:
	ASTU_PlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_RespawnComponent* RespawnComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName PlayerStartTag;

	virtual void GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn) override;

private:
	void PausePressed();

	UFUNCTION()
	void HandleOnGameMatchStateChanged(ESTU_GameMatchState GameMatchState);
};
