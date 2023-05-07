// Stay Tuned Up Game


#include "UI/STU_MenuWidget.h"

#include "Components/Button.h"
#include "STU_GameInstance.h"

void USTU_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ThisClass::HandleOnClickedStartGame);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &ThisClass::HandleOnClickedExitGame);
	}
}

void USTU_MenuWidget::HandleOnClickedStartGame()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->StartLevel(STU_GameInstance->GetDiskLevelName());
	}
}

void USTU_MenuWidget::HandleOnClickedExitGame()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->ExitGame();
	}
}
