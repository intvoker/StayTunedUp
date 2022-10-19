// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTUWeaponComponent();

	void Fire();
	void StopFiring();

	void SwitchWeapon();

	UFUNCTION()
	void OnOwnerDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

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
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	void InitAnimNotifies();

	void SpawnWeapons();

	void EquipWeapon(ASTUBaseWeapon* Weapon);

	void AttachWeaponToSocket(USceneComponent* Parent, ASTUBaseWeapon* Weapon, FName& WeaponSocketName);

	ASTUBaseWeapon* SelectNextWeapon(ASTUBaseWeapon* OtherWeapon);

	UFUNCTION()
	void OnEquipFinishedNotify(USkeletalMeshComponent* MeshComp);
};
