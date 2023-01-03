// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GamePausedWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GamePausedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void HandleOnClickedClearPause();
};
