// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PlayerStatesWidget.generated.h"

class ASTU_PlayerState;
class USTU_PlayerStateWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PlayerStatesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerStates(TArray<ASTU_PlayerState*> PlayerStates) const;

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerStatesVerticalBox;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStateWidgetClass;

private:
	USTU_PlayerStateWidget* CreatePlayerStateWidget(const ASTU_PlayerState* PlayerState) const;
};
