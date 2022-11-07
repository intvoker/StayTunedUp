// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponEffectsComponent.generated.h"

USTRUCT(BlueprintType)
struct FSTU_DecalData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UMaterial* Material;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FVector Size = FVector(10.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float LifeSpan = 10.0f;
};

USTRUCT(BlueprintType)
struct FSTU_ImpactData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* Effect;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	FSTU_DecalData DecalData;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_WeaponEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_WeaponEffectsComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SpawnImpactEffect(const FHitResult& HitResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FSTU_ImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TMap<UPhysicalMaterial*, FSTU_ImpactData> ImpactDataMap;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
