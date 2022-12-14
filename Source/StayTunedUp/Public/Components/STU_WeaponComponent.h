// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponComponent.generated.h"

class ASTU_Weapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponZoomSignature, float, ZoomFOV);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeaponStopZoomingSignature);

USTRUCT(BlueprintType)
struct FSTU_WeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* ReloadAnimMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TSubclassOf<ASTU_Weapon> WeaponClass;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_WeaponComponent();

	FWeaponZoomSignature OnWeaponZoom;
	FWeaponStopZoomingSignature OnWeaponStopZooming;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopFiring();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Zoom();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopZooming();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void LockWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnlockWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SwitchWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SwitchWeaponWithAmmo();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SwitchToWeapon(ASTU_Weapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	void OnOwnerDeath();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ASTU_Weapon* GetCurrentWeapon() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	float GetWeaponAmmoPercent(TSubclassOf<ASTU_Weapon> WeaponClass) const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool TryAddClip(TSubclassOf<ASTU_Weapon> WeaponClass, float ClipAmount);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* EquipAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TArray<FSTU_WeaponData> WeaponDataArray;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	FName WeaponAttachPointSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	FName SecondaryWeaponAttachPointSocketName = "SecondaryWeaponPoint";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bAutoSwitchWeapon = false;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool bPressedFire = false;

	bool bWeaponLocked = false;
	bool bEquipInProgress = false;
	bool bReloadInProgress = false;

	UPROPERTY()
	ASTU_Weapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTU_Weapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool IsWeaponBlocked() const;

	void InitAnimNotifies();

	UFUNCTION()
	void HandleOnNotifyEquipFinished(USkeletalMeshComponent* MeshComp);

	UFUNCTION()
	void HandleOnNotifyReloadFinished(USkeletalMeshComponent* MeshComp);

	bool IsOwnerMesh(const USkeletalMeshComponent* MeshComp) const;

	void SpawnWeapons();

	UFUNCTION()
	void HandleOnClipEmpty(ASTU_Weapon* Weapon);

	void EquipWeapon(ASTU_Weapon* Weapon);

	void AttachWeaponToSocket(USceneComponent* Parent, ASTU_Weapon* Weapon, const FName& WeaponSocketName);

	ASTU_Weapon* FindWeapon(ASTU_Weapon* Weapon) const;
	ASTU_Weapon* FindNextWeapon(ASTU_Weapon* Weapon) const;
	ASTU_Weapon* FindNextWeaponWithAmmo(ASTU_Weapon* Weapon) const;
	ASTU_Weapon* FindWeaponByClass(TSubclassOf<ASTU_Weapon> WeaponClass) const;

	UAnimMontage* FindReloadAnimMontage(ASTU_Weapon* Weapon);

	void PlayAnimMontage(UAnimMontage* AnimMontage) const;
};
