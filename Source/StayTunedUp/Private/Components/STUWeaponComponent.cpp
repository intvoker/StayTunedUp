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

void USTUWeaponComponent::StartFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::OnOwnerDeath()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->OnOwnerDeath();
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	const auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter)
		return;

	if (!WeaponClass || WeaponAttachPointSocketName.IsNone())
		return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (!CurrentWeapon)
		return;

	CurrentWeapon->AttachToComponent(PlayerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
	                                 WeaponAttachPointSocketName);
	CurrentWeapon->SetOwner(PlayerCharacter);
}
