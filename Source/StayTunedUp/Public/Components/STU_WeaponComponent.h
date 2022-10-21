// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponComponent.generated.h"

class ASTU_Weapon;

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

	UFUNCTION()
	void OnOwnerDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASTU_Weapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName SecondaryWeaponAttachPointSocketName = "SecondaryWeaponPoint";

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool EquipInProgress = false;

	UPROPERTY()
	ASTU_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTU_Weapon*> Weapons;

	void InitAnimNotifies();

	void SpawnWeapons();

	void EquipWeapon(ASTU_Weapon* Weapon);

	void AttachWeaponToSocket(USceneComponent* Parent, ASTU_Weapon* Weapon, FName& WeaponSocketName);

	ASTU_Weapon* SelectNextWeapon(ASTU_Weapon* OtherWeapon);

	UFUNCTION()
	void OnEquipFinishedNotify(USkeletalMeshComponent* MeshComp);
};
