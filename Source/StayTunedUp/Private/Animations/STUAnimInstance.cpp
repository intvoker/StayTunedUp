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
	bIsFalling = STUBaseCharacter->GetCharacterMovement()->IsFalling();
	bIsRunning = STUBaseCharacter->IsRunning();
}
