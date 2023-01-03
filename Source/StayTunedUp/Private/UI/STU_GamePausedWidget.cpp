// Stay Tuned Up Game


#include "UI/STU_GamePausedWidget.h"

#include "Components/Button.h"
#include "STU_GameModeBase.h"

void USTU_GamePausedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &ThisClass::HandleOnClickedClearPause);
	}
}

void USTU_GamePausedWidget::HandleOnClickedClearPause()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->ClearPause();
	}
}
