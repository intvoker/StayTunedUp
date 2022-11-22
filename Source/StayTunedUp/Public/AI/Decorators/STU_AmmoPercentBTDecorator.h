// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_AmmoPercentBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_AmmoPercentBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	USTU_AmmoPercentBTDecorator();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AmmoPercent = 0.5f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
