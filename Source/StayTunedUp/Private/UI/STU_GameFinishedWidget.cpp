// Stay Tuned Up Game


#include "UI/STU_GameFinishedWidget.h"

#include "Components/Button.h"
#include "STU_GameModeBase.h"

void USTU_GameFinishedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartLevelButton)
	{
		RestartLevelButton->OnClicked.AddDynamic(this, &ThisClass::OnRestartLevelButton);
	}
}

void USTU_GameFinishedWidget::OnRestartLevelButton()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->RestartCurrentLevel();
	}
}
