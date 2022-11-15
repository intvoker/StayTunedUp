// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UBTTask_STU_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API UUBTTask_STU_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUBTTask_STU_FindRandomLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector RandomLocationKey;
};
