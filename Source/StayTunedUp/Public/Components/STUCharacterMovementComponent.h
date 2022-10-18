// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Running",
		meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float MaxRunSpeed = 1200.0f;
};
