// Stay Tuned Up Game

#pragma once

#include "STU_Types.generated.h"

UENUM(BlueprintType)
enum class ESTU_GameRules : uint8
{
	TDM = 0,
	RPS
};

UENUM(BlueprintType)
enum class ESTU_GameMatchState : uint8
{
	None = 0,
	Started,
	Paused,
	Finished
};
