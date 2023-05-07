// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GamePausedWidget.generated.h"

class UButton;
class USTU_PlayerStatesWidget;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GamePausedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	USTU_PlayerStatesWidget* PlayerStatesWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void HandleOnClickedClearPause();

	void HandleOnNativeVisibilityChanged(ESlateVisibility InVisibility);
};
