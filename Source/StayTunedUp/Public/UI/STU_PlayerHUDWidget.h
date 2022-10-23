// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent();
};
