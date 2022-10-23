// Stay Tuned Up Game


#include "Components/STU_WeaponComponent.h"

#include "Animations/STU_EquipFinishedAnimNotify.h"
#include "Animations/STU_ReloadFinishedAnimNotify.h"
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
	if (EquipInProgress || ReloadInProgress)
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
	if (EquipInProgress || ReloadInProgress)
		return;

	StopFiring();
	EquipWeapon(FindNextWeapon(CurrentWeapon));

	EquipInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void USTU_WeaponComponent::Reload()
{
	if (EquipInProgress || ReloadInProgress)
		return;

	StopFiring();

	ReloadInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
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
	SwitchWeapon();
}

void USTU_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Weapons.Empty();
	CurrentWeapon = nullptr;
}

void USTU_WeaponComponent::InitAnimNotifies()
{
	if (const auto EquipAnimNotify = FindNotifyByClass<USTU_EquipFinishedAnimNotify>(EquipAnimMontage))
	{
		EquipAnimNotify->OnNotify.AddDynamic(this, &ThisClass::OnEquipFinishedNotify);
	}

	for (const auto [ReloadAnimMontage, WeaponClass] : WeaponDataArray)
	{
		if (const auto ReloadAnimNotify = FindNotifyByClass<USTU_ReloadFinishedAnimNotify>(ReloadAnimMontage))
		{
			ReloadAnimNotify->OnNotify.AddDynamic(this, &ThisClass::OnReloadFinishedNotify);
		}
	}
}

template <typename T>
T* USTU_WeaponComponent::FindNotifyByClass(UAnimSequenceBase* AnimSequenceBase)
{
	if (!AnimSequenceBase)
		return nullptr;

	for (auto AnimNotifyEvent : AnimSequenceBase->Notifies)
	{
		if (auto AnimNotify = Cast<T>(AnimNotifyEvent.Notify))
		{
			return AnimNotify;
		}
	}

	return nullptr;
}

void USTU_WeaponComponent::OnEquipFinishedNotify(USkeletalMeshComponent* MeshComp)
{
	if (!IsOwnerMesh(MeshComp))
		return;

	EquipInProgress = false;
}

void USTU_WeaponComponent::OnReloadFinishedNotify(USkeletalMeshComponent* MeshComp)
{
	if (!IsOwnerMesh(MeshComp))
		return;

	ReloadInProgress = false;
}

bool USTU_WeaponComponent::IsOwnerMesh(const USkeletalMeshComponent* MeshComp) const
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return false;

	return Character->GetMesh() == MeshComp;
}

void USTU_WeaponComponent::SpawnWeapons()
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	for (auto WeaponData : WeaponDataArray)
	{
		auto Weapon = GetWorld()->SpawnActor<ASTU_Weapon>(WeaponData.WeaponClass);
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
		AttachWeaponToSocket(Character->GetMesh(), CurrentWeapon, SecondaryWeaponAttachPointSocketName);
	}

	CurrentWeapon = Weapon;
	AttachWeaponToSocket(Character->GetMesh(), CurrentWeapon, WeaponAttachPointSocketName);

	CurrentReloadAnimMontage = FindReloadAnimMontage(CurrentWeapon);
}

void USTU_WeaponComponent::AttachWeaponToSocket(USceneComponent* Parent, ASTU_Weapon* Weapon, FName& WeaponSocketName)
{
	if (WeaponSocketName.IsNone())
		return;

	Weapon->AttachToComponent(Parent, FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
}

ASTU_Weapon* USTU_WeaponComponent::FindNextWeapon(ASTU_Weapon* Weapon)
{
	return *Weapons.FindByPredicate([Weapon](const ASTU_Weapon* WeaponElem) { return WeaponElem != Weapon; });
}

UAnimMontage* USTU_WeaponComponent::FindReloadAnimMontage(ASTU_Weapon* Weapon)
{
	const auto FoundWeaponData = WeaponDataArray.FindByPredicate([Weapon](const FSTU_WeaponData& WeaponDataElem)
	{
		return WeaponDataElem.WeaponClass == Weapon->GetClass();
	});
	return FoundWeaponData ? FoundWeaponData->ReloadAnimMontage : nullptr;
}

void USTU_WeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	Character->PlayAnimMontage(AnimMontage);
}
