// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "STU_DamageController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STAYTUNEDUP_API ASTU_DamageController : public AController
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;
};
