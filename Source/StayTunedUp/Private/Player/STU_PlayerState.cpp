// Stay Tuned Up Game


#include "Player/STU_PlayerState.h"

FString ASTU_PlayerState::GetPlayerStateInfo() const
{
	return FString::Printf(
		TEXT("TeamID: %d. Kills: %d. FriendlyKills: %d. Deaths: %d."), TeamID, Kills, FriendlyKills, Deaths);
}
