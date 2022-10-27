// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClipEmptySignature);

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

USTRUCT(BlueprintType)
struct FSTU_WeaponUIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* CrosshairIcon;
};

UCLASS()
class STAYTUNEDUP_API ASTU_Weapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTU_Weapon();

	FClipEmptySignature OnClipEmpty;

	virtual void Fire();
	virtual void StopFiring();

	bool IsAmmoEmpty() const;
	bool CanUseClip() const;
	void UseClip();
	bool CanUseRound() const;
	void UseRound();
	void LogAmmo();

	void OnOwnerDeath();

	FSTU_WeaponUIData GetWeaponUIData() const { return WeaponUIData; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleFlashSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float MaxRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FSTU_AmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FSTU_WeaponUIData WeaponUIData;

	UPROPERTY(EditDefaultsOnly, Category = "Life")
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
};
