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

void USTUWeaponComponent::StopFiring()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFiring();
}

void USTUWeaponComponent::SwitchWeapon()
{
	EquipWeapon(SelectNextWeapon(CurrentWeapon));
}

void USTUWeaponComponent::OnOwnerDeath()
{
	StopFiring();

	for (auto Weapon : Weapons)
	{
		Weapon->OnOwnerDeath();
	}
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
	EquipWeapon(SelectNextWeapon(CurrentWeapon));
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Weapons.Empty();
	CurrentWeapon = nullptr;
}

void USTUWeaponComponent::SpawnWeapons()
{
	const auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter)
		return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
		if (!Weapon)
			continue;

		Weapon->SetOwner(PlayerCharacter);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(PlayerCharacter->GetMesh(), Weapon, SecondaryWeaponAttachPointSocketName);
	}
}

void USTUWeaponComponent::EquipWeapon(ASTUBaseWeapon* Weapon)
{
	if (!Weapon || Weapon == CurrentWeapon)
		return;

	const auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter)
		return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFiring();
		AttachWeaponToSocket(PlayerCharacter->GetMesh(), CurrentWeapon, SecondaryWeaponAttachPointSocketName);
	}

	CurrentWeapon = Weapon;
	AttachWeaponToSocket(PlayerCharacter->GetMesh(), CurrentWeapon, WeaponAttachPointSocketName);
}

void USTUWeaponComponent::AttachWeaponToSocket(USceneComponent* Parent, ASTUBaseWeapon* Weapon, FName& WeaponSocketName)
{
	if (WeaponSocketName.IsNone())
		return;

	Weapon->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
}

ASTUBaseWeapon* USTUWeaponComponent::SelectNextWeapon(ASTUBaseWeapon* OtherWeapon)
{
	for (auto Weapon : Weapons)
	{
		if (Weapon != OtherWeapon)
		{
			return Weapon;
		}
	}

	return nullptr;
}