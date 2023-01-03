// Stay Tuned Up Game


#include "UI/STU_GameFinishedWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Player/STU_PlayerState.h"
#include "STU_GameInstance.h"
#include "STU_GameModeBase.h"
#include "UI/STU_PlayerStateWidget.h"

void USTU_GameFinishedWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
		SetPlayerStates(STU_GameModeBase->GetPlayerStates());
	}
}

void USTU_GameFinishedWidget::SetPlayerStates(TArray<ASTU_PlayerState*> PlayerStates) const
{
	if (!PlayerStatesVerticalBox)
		return;

	PlayerStatesVerticalBox->ClearChildren();

	ASTU_PlayerState* PlayerStateTotal = NewObject<ASTU_PlayerState>();
	PlayerStateTotal->SetPlayerName("Total");

	for (const auto PlayerState : PlayerStates)
	{
		const auto PlayerStateWidget = CreatePlayerStateWidget(PlayerState);
		if (!PlayerStateWidget)
			continue;

		PlayerStatesVerticalBox->AddChild(PlayerStateWidget);

		PlayerStateTotal->SetKills(PlayerStateTotal->GetKills() + PlayerState->GetKills());
		PlayerStateTotal->SetFriendlyKills(PlayerStateTotal->GetFriendlyKills() + PlayerState->GetFriendlyKills());
		PlayerStateTotal->SetDeaths(PlayerStateTotal->GetDeaths() + PlayerState->GetDeaths());
	}

	const auto PlayerStateTotalWidget = CreatePlayerStateWidget(PlayerStateTotal);
	if (!PlayerStateTotalWidget)
		return;

	PlayerStatesVerticalBox->AddChild(PlayerStateTotalWidget);
}

USTU_PlayerStateWidget* USTU_GameFinishedWidget::CreatePlayerStateWidget(const ASTU_PlayerState* PlayerState) const
{
	const auto PlayerStateWidget = CreateWidget<USTU_PlayerStateWidget>(GetWorld(), PlayerStateWidgetClass);
	if (!PlayerStateWidget)
		return nullptr;

	PlayerStateWidget->SetPlayerState(PlayerState);

	return PlayerStateWidget;
}
