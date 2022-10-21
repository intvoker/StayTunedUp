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

	const auto ComponentOwner = Cast<ACharacter>(GetOwner());
	if (!ComponentOwner)
		return;

	ComponentOwner->LandedDelegate.AddDynamic(this, &ThisClass::OnLandedCallback);
}

void USTU_FallDamageComponent::OnLandedCallback(const FHitResult& Hit)
{
	const auto ComponentOwner = Cast<ACharacter>(GetOwner());
	if (!ComponentOwner)
		return;

	const auto VelocityZ = FMath::Abs(ComponentOwner->GetVelocity().Z);

	//UE_LOG(LogTemp, Warning, TEXT("VelocityZ: %f"), VelocityZ);

	if (VelocityZ < FallDamageVelocity.Min)
		return;

	const auto Damage = FMath::GetMappedRangeValueClamped<float>(FallDamageVelocity.MakeRange(),
	                                                             FallDamage.MakeRange(), VelocityZ);

	ComponentOwner->TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);

	//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
}
