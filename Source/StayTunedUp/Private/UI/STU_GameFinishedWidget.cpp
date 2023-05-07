// Stay Tuned Up Game


#include "UI/STU_GameFinishedWidget.h"

#include "Components/Button.h"
#include "STU_GameInstance.h"
#include "STU_GameModeBase.h"
#include "UI/STU_PlayerStatesWidget.h"

void USTU_GameFinishedWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartLevelButton)
	{
		RestartLevelButton->OnClicked.AddDynamic(this, &ThisClass::HandleOnClickedRestartLevel);
	}

	OnNativeVisibilityChanged.AddUObject(this, &ThisClass::HandleOnNativeVisibilityChanged);
}

void USTU_GameFinishedWidget::HandleOnClickedRestartLevel()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->RestartCurrentLevel();
	}
}

void USTU_GameFinishedWidget::HandleOnNativeVisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility != ESlateVisibility::Visible)
		return;

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		PlayerStatesWidget->SetPlayerStates(STU_GameModeBase->GetPlayerStates());
	}
}
