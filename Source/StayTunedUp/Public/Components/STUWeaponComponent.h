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

	void StartFire();
	void StopFire();

	UFUNCTION()
	void OnOwnerDeath();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponAttachPointSocketName = "WeaponPoint";

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UFUNCTION()
	void SpawnWeapon();
};
