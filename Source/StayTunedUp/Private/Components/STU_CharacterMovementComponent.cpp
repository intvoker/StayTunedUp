// Stay Tuned Up Game


#include "Components/STU_CharacterMovementComponent.h"

#include "Player/STU_Character.h"

float USTU_CharacterMovementComponent::GetMaxSpeed() const
{
	const auto STU_Character = Cast<ASTU_Character>(GetPawnOwner());

	return STU_Character && STU_Character->IsRunning() ? MaxRunSpeed : Super::GetMaxSpeed();
}
