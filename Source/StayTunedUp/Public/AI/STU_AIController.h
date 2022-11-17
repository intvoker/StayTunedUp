// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STU_AIController.generated.h"

class USTU_AIPerceptionComponent;
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

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName EnemyActorKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
};
