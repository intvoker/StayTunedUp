// Stay Tuned Up Game


#include "Components/STU_WeaponComponent.h"

#include "Animations/STU_AnimUtility.h"
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

	if (CurrentWeapon->IsAmmoEmpty() && bAutoSwitchWeapon)
	{
		SwitchWeaponWithAmmo();
	}
	else
	{
		CurrentWeapon->Fire();
	}
}

void USTU_WeaponComponent::StopFiring()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFiring();
}

void USTU_WeaponComponent::SwitchWeapon()
{
	const auto NextWeapon = FindNextWeapon(CurrentWeapon);
	if (!NextWeapon)
		return;

	SwitchToWeapon(NextWeapon);
}

void USTU_WeaponComponent::SwitchWeaponWithAmmo()
{
	const auto NextWeapon = FindNextWeaponWithAmmo(CurrentWeapon);
	if (!NextWeapon)
		return;

	SwitchToWeapon(NextWeapon);
}

void USTU_WeaponComponent::SwitchToWeapon(ASTU_Weapon* Weapon)
{
	if (EquipInProgress || ReloadInProgress)
		return;

	StopFiring();
	EquipWeapon(Weapon);

	EquipInProgress = true;
	PlayAnimMontage(EquipAnimMontage);
}

void USTU_WeaponComponent::Reload()
{
	if (EquipInProgress || ReloadInProgress)
		return;

	if (!CurrentWeapon)
		return;

	if (!CurrentWeapon->CanUseClip())
		return;

	StopFiring();
	CurrentWeapon->UseClip();

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

float USTU_WeaponComponent::GetWeaponAmmoPercent(TSubclassOf<ASTU_Weapon> WeaponClass) const
{
	if (!WeaponClass)
		return 0.0f;

	const auto Weapon = FindWeaponByClass(WeaponClass);
	if (!Weapon)
		return 0.0f;

	return Weapon->GetAmmoPercent();
}

bool USTU_WeaponComponent::TryAddClip(TSubclassOf<ASTU_Weapon> WeaponClass, float ClipAmount)
{
	if (!WeaponClass)
		return false;

	const auto Weapon = FindWeaponByClass(WeaponClass);
	if (!Weapon)
		return false;

	return Weapon->TryAddClip(ClipAmount);
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
	if (const auto EquipAnimNotify = STU_AnimUtility::FindNotifyByClass<USTU_EquipFinishedAnimNotify>(EquipAnimMontage))
	{
		EquipAnimNotify->OnNotify.AddDynamic(this, &ThisClass::OnEquipFinishedNotify);
	}

	for (const auto [ReloadAnimMontage, WeaponClass] : WeaponDataArray)
	{
		if (const auto ReloadAnimNotify = STU_AnimUtility::FindNotifyByClass<USTU_ReloadFinishedAnimNotify>(
			ReloadAnimMontage))
		{
			ReloadAnimNotify->OnNotify.AddDynamic(this, &ThisClass::OnReloadFinishedNotify);
		}
	}
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
		{
			continue;
		}

		Weapon->SetOwner(Character);
		Weapon->OnClipEmpty.AddDynamic(this, &ThisClass::OnClipEmpty);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Character->GetMesh(), Weapon, SecondaryWeaponAttachPointSocketName);
	}
}

void USTU_WeaponComponent::OnClipEmpty(ASTU_Weapon* Weapon)
{
	if (!Weapon)
		return;

	const auto WeaponToReload = FindWeapon(Weapon);
	if (!WeaponToReload)
		return;

	if (WeaponToReload == CurrentWeapon)
	{
		Reload();
	}
	else
	{
		WeaponToReload->UseClip();
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

ASTU_Weapon* USTU_WeaponComponent::FindWeapon(ASTU_Weapon* Weapon) const
{
	const auto FoundWeapon = Weapons.FindByPredicate([Weapon](const ASTU_Weapon* WeaponElem)
	{
		return WeaponElem == Weapon;
	});
	return FoundWeapon ? *FoundWeapon : nullptr;
}

ASTU_Weapon* USTU_WeaponComponent::FindNextWeapon(ASTU_Weapon* Weapon) const
{
	const auto FoundWeapon = Weapons.FindByPredicate([Weapon](const ASTU_Weapon* WeaponElem)
	{
		return WeaponElem != Weapon;
	});
	return FoundWeapon ? *FoundWeapon : nullptr;
}

ASTU_Weapon* USTU_WeaponComponent::FindNextWeaponWithAmmo(ASTU_Weapon* Weapon) const
{
	const auto FoundWeapon = Weapons.FindByPredicate([Weapon](const ASTU_Weapon* WeaponElem)
	{
		return WeaponElem != Weapon && !WeaponElem->IsAmmoEmpty();
	});
	return FoundWeapon ? *FoundWeapon : nullptr;
}

ASTU_Weapon* USTU_WeaponComponent::FindWeaponByClass(TSubclassOf<ASTU_Weapon> WeaponClass) const
{
	const auto FoundWeapon = Weapons.FindByPredicate([WeaponClass](const ASTU_Weapon* WeaponElem)
	{
		return WeaponElem->IsA(WeaponClass);
	});
	return FoundWeapon ? *FoundWeapon : nullptr;
}

UAnimMontage* USTU_WeaponComponent::FindReloadAnimMontage(ASTU_Weapon* Weapon)
{
	const auto FoundWeaponData = WeaponDataArray.FindByPredicate([Weapon](const FSTU_WeaponData& WeaponDataElem)
	{
		return Weapon->IsA(WeaponDataElem.WeaponClass);
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
