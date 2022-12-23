// Stay Tuned Up Game


#include "UI/STU_MenuWidget.h"

#include "Components/Button.h"
#include "STU_MenuGameModeBase.h"

void USTU_MenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGameButton);
	}
}

void USTU_MenuWidget::OnStartGameButton()
{
	if (const auto STU_MenuGameModeBase = GetWorld()->GetAuthGameMode<ASTU_MenuGameModeBase>())
	{
		STU_MenuGameModeBase->StartLevel("TestLevel");
	}
}
