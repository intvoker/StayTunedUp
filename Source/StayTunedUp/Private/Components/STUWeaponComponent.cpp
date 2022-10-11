// Stay Tuned Up Game


#include "Components/STUWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapons/STUBaseWeapon.h"

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTUWeaponComponent::Fire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->Fire();
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	const auto ComponentOwner = Cast<ACharacter>(GetOwner());
	if (!ComponentOwner)
		return;

	if (!WeaponClass || WeaponAttachPoint.IsNone())
		return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
		return;

	CurrentWeapon->AttachToComponent(ComponentOwner->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
	                                 WeaponAttachPoint);
}
