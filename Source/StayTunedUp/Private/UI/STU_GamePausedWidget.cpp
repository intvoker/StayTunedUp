// Stay Tuned Up Game


#include "UI/STU_GamePausedWidget.h"

#include "STU_GameModeBase.h"
#include "Components/Button.h"

bool USTU_GamePausedWidget::Initialize()
{
	const auto bInitializedSet = Super::Initialize();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &ThisClass::OnClearPauseButton);
	}

	return bInitializedSet;
}

void USTU_GamePausedWidget::OnClearPauseButton()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->ClearPause();
	}
}
