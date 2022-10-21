// Stay Tuned Up Game


#include "Animations/STU_AnimInstance.h"

#include "Animations/STU_AnimUtility.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/STU_Character.h"

void USTU_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	STU_Character = Cast<ASTU_Character>(TryGetPawnOwner());
}

void USTU_AnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	if (!STU_Character)
		return;

	Speed = STU_Character->GetVelocity().Size();
	MovementOffsetYaw = STU_AnimUtility::GetMovementOffsetYaw(STU_Character);

	AimOffsetPitch = STU_Character->GetBaseAimRotation().Pitch;
	AimOffsetYaw = STU_Character->GetBaseAimRotation().Yaw;

	bIsFalling = STU_Character->GetCharacterMovement()->IsFalling();
	bIsRunning = STU_Character->IsRunning();

	/*
	const auto Start = STU_Character->GetActorLocation();
	const auto ForwardNormal = STU_Character->GetActorForwardVector();
	const auto VelocityNormal = STU_Character->GetVelocity().GetSafeNormal();

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
