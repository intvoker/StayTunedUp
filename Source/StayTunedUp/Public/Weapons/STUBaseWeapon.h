// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class STAYTUNEDUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	virtual void Fire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName MuzzleFlashSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float MaxRange = 1500.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MakeShot();

	void GetPlayerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection);
	void GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection);
};
