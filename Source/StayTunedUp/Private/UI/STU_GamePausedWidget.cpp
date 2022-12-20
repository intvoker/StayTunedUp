// Stay Tuned Up Game


#include "UI/STU_GamePausedWidget.h"

#include "Components/Button.h"
#include "STU_GameModeBase.h"

void USTU_GamePausedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &ThisClass::OnClearPauseButton);
	}
}

void USTU_GamePausedWidget::OnClearPauseButton()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->ClearPause();
	}
}
