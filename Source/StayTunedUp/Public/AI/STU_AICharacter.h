// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_AICharacter : public ASTU_Character
{
	GENERATED_BODY()

public:
	ASTU_AICharacter(const FObjectInitializer& ObjectInitializer);
};
