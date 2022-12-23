// Stay Tuned Up Game


#include "UI/STU_MenuWidget.h"

#include "Components/Button.h"
#include "STU_GameInstance.h"

void USTU_MenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ThisClass::OnStartGameButton);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &ThisClass::OnExitGameButton);
	}
}

void USTU_MenuWidget::OnStartGameButton()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->StartLevel(STU_GameInstance->GetTestLevelName());
	}
}

void USTU_MenuWidget::OnExitGameButton()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->ExitGame();
	}
}
