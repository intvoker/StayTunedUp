// Stay Tuned Up Game


#include "Animations/STUAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

void USTUAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	STUBaseCharacter = Cast<ASTUBaseCharacter>(TryGetPawnOwner());
}

void USTUAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!STUBaseCharacter)
		return;

	Speed = STUBaseCharacter->GetVelocity().Size();
	MovementOffsetYaw = STUBaseCharacter->GetMovementOffsetYaw();

	bIsFalling = STUBaseCharacter->GetCharacterMovement()->IsFalling();
	bIsRunning = STUBaseCharacter->IsRunning();

	/*
	const FString MovementOffsetYawMessage = FString::Printf(TEXT("Movement Offset Yaw: %f"), MovementOffsetYaw);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::White, MovementOffsetYawMessage, false);
	}
	*/
}
