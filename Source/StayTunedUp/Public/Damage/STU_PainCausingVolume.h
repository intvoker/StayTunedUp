// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PainCausingVolume.h"
#include "STU_PainCausingVolume.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STAYTUNEDUP_API ASTU_PainCausingVolume : public APainCausingVolume
{
	GENERATED_BODY()

public:
	int32 GetTeamID() const { return TeamID; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 TeamID = 0;
};
