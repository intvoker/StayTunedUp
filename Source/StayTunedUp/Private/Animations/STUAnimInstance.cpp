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

	AimOffsetPitch = STUBaseCharacter->GetBaseAimRotation().Pitch;
	AimOffsetYaw = STUBaseCharacter->GetBaseAimRotation().Yaw;

	bIsFalling = STUBaseCharacter->GetCharacterMovement()->IsFalling();
	bIsRunning = STUBaseCharacter->IsRunning();

	/*
	const auto Start = STUBaseCharacter->GetActorLocation();
	const auto ForwardNormal = STUBaseCharacter->GetActorForwardVector();
	const auto VelocityNormal = STUBaseCharacter->GetVelocity().GetSafeNormal();

	DrawDebugLine(GetWorld(), Start, Start + ForwardNormal * 500, FColor::Red, false, -1, 0, 10);
	DrawDebugLine(GetWorld(), Start, Start + VelocityNormal * 500, FColor::Blue, false, -1, 0, 10);

	const FString ForwardNormalMessage = FString::Printf(TEXT("ForwardNormal: %s"), *ForwardNormal.ToString());
	const FString VelocityNormalMessage = FString::Printf(TEXT("VelocityNormal: %s"), *VelocityNormal.ToString());
	const FString MovementOffsetYawMessage = FString::Printf(TEXT("MovementOffsetYaw: %f"), MovementOffsetYaw);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::White, ForwardNormalMessage, false);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::White, VelocityNormalMessage, false);
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::White, MovementOffsetYawMessage, false);
	}
	*/
}
