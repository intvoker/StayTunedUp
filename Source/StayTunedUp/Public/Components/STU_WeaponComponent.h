// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponComponent.generated.h"

class ASTU_Weapon;

USTRUCT(BlueprintType)
struct FSTU_WeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* ReloadAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTU_Weapon> WeaponClass;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_WeaponComponent();

	void Fire();
	void StopFiring();

	void SwitchWeapon();

	void Reload();

	UFUNCTION()
	void OnOwnerDeath();

	ASTU_Weapon* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FSTU_WeaponData> WeaponDataArray;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SecondaryWeaponAttachPointSocketName = "SecondaryWeaponPoint";

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool EquipInProgress = false;
	bool ReloadInProgress = false;

	UPROPERTY()
	ASTU_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTU_Weapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	void InitAnimNotifies();

	UFUNCTION()
	void OnEquipFinishedNotify(USkeletalMeshComponent* MeshComp);

	UFUNCTION()
	void OnReloadFinishedNotify(USkeletalMeshComponent* MeshComp);

	bool IsOwnerMesh(const USkeletalMeshComponent* MeshComp) const;

	void SpawnWeapons();

	UFUNCTION()
	void OnClipEmpty();

	void EquipWeapon(ASTU_Weapon* Weapon);

	void AttachWeaponToSocket(USceneComponent* Parent, ASTU_Weapon* Weapon, FName& WeaponSocketName);

	ASTU_Weapon* FindNextWeapon(ASTU_Weapon* Weapon);

	UAnimMontage* FindReloadAnimMontage(ASTU_Weapon* Weapon);

	void PlayAnimMontage(UAnimMontage* AnimMontage);
};
