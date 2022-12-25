// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_EffectComponent.generated.h"

class USoundCue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_EffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_EffectComponent();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void SetupEffectAttachment(USceneComponent* InParent, FName InSocketName = NAME_None);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void Spawn();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void Despawn();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* SoundCue;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	bool bRevertSoundBehavior = false;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	bool bStopSoundOnDespawn = true;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY()
	UAudioComponent* AudioComponent;
};
