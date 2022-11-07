// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class USTU_WeaponEffectsComponent;

UCLASS()
class STAYTUNEDUP_API ASTU_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTU_Projectile();

	void SetProjectileDirection(FVector ProjectileDirectionParam) { ProjectileDirection = ProjectileDirectionParam; };

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_WeaponEffectsComponent* WeaponEffectsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	bool bDoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float LifeSpan = 10.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector ProjectileDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     FVector NormalImpulse, const FHitResult& Hit);
};
