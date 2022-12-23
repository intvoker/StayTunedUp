// Stay Tuned Up Game


#include "UI/STU_GameFinishedWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "STU_GameInstance.h"
#include "STU_GameModeBase.h"
#include "UI/STU_PlayerStateWidget.h"

void USTU_GameFinishedWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartLevelButton)
	{
		RestartLevelButton->OnClicked.AddDynamic(this, &ThisClass::OnRestartLevelButton);
	}

	OnNativeVisibilityChanged.AddUObject(this, &ThisClass::OnWidgetVisibilityChanged);
}

void USTU_GameFinishedWidget::OnRestartLevelButton()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->RestartCurrentLevel();
	}
}

void USTU_GameFinishedWidget::OnWidgetVisibilityChanged(ESlateVisibility InVisibility)
{
	if (InVisibility != ESlateVisibility::Visible)
		return;

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		SetPlayerStates(STU_GameModeBase->GetPlayerStates());
	}
}

void USTU_GameFinishedWidget::SetPlayerStates(TArray<ASTU_PlayerState*> PlayerStates) const
{
	if (!PlayerStatesVerticalBox)
		return;

	PlayerStatesVerticalBox->ClearChildren();

	for (const auto PlayerState : PlayerStates)
	{
		const auto PlayerStateWidget = CreateWidget<USTU_PlayerStateWidget>(GetWorld(), PlayerStateWidgetClass);
		if (!PlayerStateWidget)
			continue;

		PlayerStateWidget->SetPlayerState(PlayerState);
		PlayerStatesVerticalBox->AddChild(PlayerStateWidget);
	}
}
