// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_AICharacter.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_AICharacter : public ASTU_Character
{
	GENERATED_BODY()

public:
	ASTU_AICharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;
};
