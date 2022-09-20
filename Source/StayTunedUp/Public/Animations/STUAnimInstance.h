// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "STUAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTUAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASTUBaseCharacter* STUBaseCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MovementOffsetYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRunning;
};
