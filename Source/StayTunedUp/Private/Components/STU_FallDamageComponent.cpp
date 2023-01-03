// Stay Tuned Up Game


#include "Components/STU_FallDamageComponent.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
USTU_FallDamageComponent::USTU_FallDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void USTU_FallDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	Character->LandedDelegate.AddDynamic(this, &ThisClass::HandleLandedDelegate);
}

void USTU_FallDamageComponent::HandleLandedDelegate(const FHitResult& Hit)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	const auto VelocityZ = FMath::Abs(Character->GetVelocity().Z);

	//UE_LOG(LogTemp, Warning, TEXT("VelocityZ: %f"), VelocityZ);

	if (VelocityZ < FallDamageVelocity.Min)
		return;

	const auto Damage = FMath::GetMappedRangeValueClamped<float>(FallDamageVelocity.MakeRange(),
	                                                             FallDamage.MakeRange(), VelocityZ);

	Character->TakeDamage(Damage, FDamageEvent(), Character->GetController(), Character);

	//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
}
