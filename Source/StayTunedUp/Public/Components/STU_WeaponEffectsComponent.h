// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_WeaponEffectsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_WeaponEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_WeaponEffectsComponent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PlayImpactEffect(const FHitResult& HitResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TMap<UPhysicalMaterial*, UParticleSystem*> ImpactEffects;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
