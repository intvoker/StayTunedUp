// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "STU_PickupEnvQueryTest.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PickupEnvQueryTest : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	USTU_PickupEnvQueryTest(const FObjectInitializer& ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
