// Stay Tuned Up Game


#include "UI/STU_PlayerStatesWidget.h"

#include "Components/VerticalBox.h"
#include "Player/STU_PlayerState.h"
#include "UI/STU_PlayerStateWidget.h"

void USTU_PlayerStatesWidget::SetPlayerStates(TArray<ASTU_PlayerState*> PlayerStates) const
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

USTU_PlayerStateWidget* USTU_PlayerStatesWidget::CreatePlayerStateWidget(const ASTU_PlayerState* PlayerState) const
{
	const auto PlayerStateWidget = CreateWidget<USTU_PlayerStateWidget>(GetWorld(), PlayerStateWidgetClass);
	if (!PlayerStateWidget)
		return nullptr;

	PlayerStateWidget->SetPlayerState(PlayerState);

	return PlayerStateWidget;
}
