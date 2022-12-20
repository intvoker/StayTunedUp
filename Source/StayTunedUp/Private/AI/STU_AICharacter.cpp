// Stay Tuned Up Game


#include "AI/STU_AICharacter.h"

#include "AI/STU_AIController.h"
#include "BrainComponent.h"
#include "Components/STU_AIWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTU_AICharacter::ASTU_AICharacter(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTU_AIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTU_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
	}
}

void ASTU_AICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = GetController<AAIController>();
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
