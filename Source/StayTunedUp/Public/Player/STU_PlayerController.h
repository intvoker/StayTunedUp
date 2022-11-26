// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName PlayerStartTag;
};
