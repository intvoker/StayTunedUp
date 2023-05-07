// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GameFinishedWidget.generated.h"

class UButton;
class USTU_PlayerStatesWidget;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GameFinishedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	USTU_PlayerStatesWidget* PlayerStatesWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartLevelButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void HandleOnClickedRestartLevel();

	void HandleOnNativeVisibilityChanged(ESlateVisibility InVisibility);
};
