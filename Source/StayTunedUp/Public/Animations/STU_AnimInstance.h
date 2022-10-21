// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "STU_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASTU_Character* STU_Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AimOffsetPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AimOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRunning;
};
