// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_HealthPercentBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_HealthPercentBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTU_HealthPercentBTDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.5f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
