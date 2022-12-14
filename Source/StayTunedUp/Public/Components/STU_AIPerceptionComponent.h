// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STU_AIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* FindNearestAliveEnemyActor() const;

private:
	bool CanKill(const AActor* VictimActor) const;
};
