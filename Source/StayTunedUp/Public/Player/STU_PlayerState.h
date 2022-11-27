// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STU_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	int32 GetTeamID() const { return TeamID; }
	void SetTeamID(int32 TeamIDParam) { TeamID = TeamIDParam; }

	FLinearColor GetTeamColor() const { return TeamColor; }
	void SetTeamColor(FLinearColor TeamColorParam) { TeamColor = TeamColorParam; }

private:
	int32 TeamID;
	FLinearColor TeamColor;
};
