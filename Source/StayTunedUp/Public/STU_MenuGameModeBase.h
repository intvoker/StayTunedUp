// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STU_MenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_MenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTU_MenuGameModeBase();

	void StartLevel(FName LevelName) const;
};
