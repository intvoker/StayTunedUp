// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STU_AIController.generated.h"

class USTU_AIPerceptionComponent;
class USTU_RespawnComponent;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_AIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTU_AIController();

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_AIPerceptionComponent* STU_AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_RespawnComponent* RespawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};
