// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PlayerStateWidget.generated.h"

class ASTU_PlayerState;
class UTextBlock;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetPlayerState(const ASTU_PlayerState* PlayerState) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerStateTextBlock;
};
