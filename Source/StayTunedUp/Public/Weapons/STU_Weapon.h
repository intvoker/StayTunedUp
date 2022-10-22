// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Weapon.generated.h"

USTRUCT(BlueprintType)
struct FSTU_AmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Rounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!bInfinite"))
	int32 Clips;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bInfinite;
};

UCLASS()
class STAYTUNEDUP_API ASTU_Weapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTU_Weapon();

	virtual void Fire();
	virtual void StopFiring();

	void OnOwnerDeath();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleFlashSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MaxRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FSTU_AmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 10.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void MakeShot();
	virtual void ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult);

	void GetPlayerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection);
	void GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection);
	virtual void GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd);

private:
	FSTU_AmmoData CurrentAmmo;

	bool IsAmmoEmpty() const;
	bool IsClipEmpty() const;
	void UseAmmo();
	void UseClip();
	void LogAmmo();
};
