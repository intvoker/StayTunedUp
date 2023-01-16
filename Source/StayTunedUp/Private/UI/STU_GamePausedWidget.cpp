// Stay Tuned Up Game


#include "UI/STU_GamePausedWidget.h"

#include "Components/Button.h"
#include "STU_GameModeBase.h"
#include "UI/STU_PlayerStatesWidget.h"

void USTU_GamePausedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &ThisClass::HandleOnClickedClearPause);
	}

	OnNativeVisibilityChanged.AddUObject(this, &ThisClass::HandleOnNativeVisibilityChanged);
}

void USTU_GamePausedWidget::HandleOnClickedClearPause()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->ClearPause();
	}
}

void USTU_GamePausedWidget::HandleOnNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility != ESlateVisibility::Visible)
		return;

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		PlayerStatesWidget->SetPlayerStates(STU_GameModeBase->GetPlayerStates());
	}
}
