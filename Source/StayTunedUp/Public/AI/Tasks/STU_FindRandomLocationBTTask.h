// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STU_FindRandomLocationBTTask.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_FindRandomLocationBTTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USTU_FindRandomLocationBTTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector CenterActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector RandomLocationKey;
};
