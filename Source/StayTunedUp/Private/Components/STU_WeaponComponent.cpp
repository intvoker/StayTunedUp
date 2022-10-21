// Stay Tuned Up Game


#include "Components/STU_WeaponComponent.h"

#include "Animations/STU_EquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapons/STU_Weapon.h"

// Sets default values for this component's properties
USTU_WeaponComponent::USTU_WeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTU_WeaponComponent::Fire()
{
	if (EquipInProgress)
		return;

	if (!CurrentWeapon)
		return;

	CurrentWeapon->Fire();
}

void USTU_WeaponComponent::StopFiring()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFiring();
}

void USTU_WeaponComponent::SwitchWeapon()
{
	if (EquipInProgress)
		return;

	EquipWeapon(SelectNextWeapon(CurrentWeapon));
}

void USTU_WeaponComponent::OnOwnerDeath()
{
	StopFiring();

	for (auto Weapon : Weapons)
	{
		Weapon->OnOwnerDeath();
	}
}

// Called when the game starts
void USTU_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimNotifies();

	SpawnWeapons();
	EquipWeapon(SelectNextWeapon(CurrentWeapon));
}

void USTU_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Weapons.Empty();
	CurrentWeapon = nullptr;
}

void USTU_WeaponComponent::InitAnimNotifies()
{
	if (!EquipAnimMontage)
		return;

	for (auto AnimNotifyEvent : EquipAnimMontage->Notifies)
	{
		if (auto EquipAnimNotify = Cast<USTU_EquipFinishedAnimNotify>(AnimNotifyEvent.Notify))
		{
			EquipAnimNotify->OnEquipFinishedNotify.AddDynamic(this, &ThisClass::OnEquipFinishedNotify);
			break;
		}
	}
}

void USTU_WeaponComponent::OnEquipFinishedNotify(USkeletalMeshComponent* MeshComp)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (Character->GetMesh() != MeshComp)
		return;

	EquipInProgress = false;
}

void USTU_WeaponComponent::SpawnWeapons()
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTU_Weapon>(WeaponClass);
		if (!Weapon)
			continue;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Character->GetMesh(), Weapon, SecondaryWeaponAttachPointSocketName);
	}
}

void USTU_WeaponComponent::EquipWeapon(ASTU_Weapon* Weapon)
{
	if (!Weapon || Weapon == CurrentWeapon)
		return;

	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFiring();
		AttachWeaponToSocket(Character->GetMesh(), CurrentWeapon, SecondaryWeaponAttachPointSocketName);
	}

	CurrentWeapon = Weapon;
	AttachWeaponToSocket(Character->GetMesh(), CurrentWeapon, WeaponAttachPointSocketName);

	EquipInProgress = true;
	Character->PlayAnimMontage(EquipAnimMontage);
}

void USTU_WeaponComponent::AttachWeaponToSocket(USceneComponent* Parent, ASTU_Weapon* Weapon, FName& WeaponSocketName)
{
	if (WeaponSocketName.IsNone())
		return;

	Weapon->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
}

ASTU_Weapon* USTU_WeaponComponent::SelectNextWeapon(ASTU_Weapon* OtherWeapon)
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
