// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_FindEnemyBTService.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_FindEnemyBTService : public UBTService
{
	GENERATED_BODY()

public:
	USTU_FindEnemyBTService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
