// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STU_EnemyActorEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STAYTUNEDUP_API USTU_EnemyActorEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	bool bUseQuerier = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!bUseQuerier"))
	FName EnemyActorKeyName = "EnemyActor";
};
