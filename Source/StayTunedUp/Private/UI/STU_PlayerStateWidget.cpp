// Stay Tuned Up Game


#include "UI/STU_PlayerStateWidget.h"

#include "Components/TextBlock.h"
#include "Player/STU_PlayerState.h"

void USTU_PlayerStateWidget::SetPlayerState(const ASTU_PlayerState* PlayerState) const
{
	if (!PlayerState)
		return;

	const auto PlayerStateInfo = FString::Printf(
		TEXT("Name: %s. Team ID: %d. Kills: %d. Friendly Kills: %d. Deaths: %d."), *PlayerState->GetPlayerName(),
		PlayerState->GetTeamID(), PlayerState->GetKills(), PlayerState->GetFriendlyKills(), PlayerState->GetDeaths());

	PlayerStateTextBlock->SetText(FText::FromString(PlayerStateInfo));
}
