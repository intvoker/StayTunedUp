// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GameFinishedWidget.generated.h"

class ASTU_PlayerState;
class UButton;
class USTU_PlayerStateWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GameFinishedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartLevelButton;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatesVerticalBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStateWidgetClass;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnRestartLevelButton();

	void OnWidgetVisibilityChanged(ESlateVisibility InVisibility);

	void SetPlayerStates(TArray<ASTU_PlayerState*> PlayerStates) const;

	USTU_PlayerStateWidget* CreatePlayerStateWidget(const ASTU_PlayerState* PlayerState) const;
};
