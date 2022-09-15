// Stay Tuned Up Game


#include "Components/STUCharacterMovementComponent.h"

#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const auto STUBaseCharacter = Cast<ASTUBaseCharacter>(GetPawnOwner());

	return STUBaseCharacter && STUBaseCharacter->IsRunning() ? MaxRunSpeed : Super::GetMaxSpeed();
}
