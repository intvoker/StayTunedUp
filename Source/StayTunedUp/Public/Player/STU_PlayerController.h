// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_ControllerViewPointInterface.h"
#include "STU_Types.h"
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
	bool bOnlySpectator = false;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (EditCondition = "bOnlySpectator"))
	bool bRotateSpectator = false;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (EditCondition = "bOnlySpectator"))
	FVector RotationAxis = FVector::UpVector;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (EditCondition = "bOnlySpectator"))
	FVector RotationPoint = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (EditCondition = "bOnlySpectator"))
	float RotationSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName PlayerStartTag;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName SpectatorStartTag;

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	FName GetStartTag() const;
	bool IsStartTag(const FName& StartTag) const;

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	virtual void SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn) override;

private:
	void PausePressed();

	UFUNCTION()
	void HandleOnGameMatchStateChanged(ESTU_GameMatchState GameMatchState);
};
