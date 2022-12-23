// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
