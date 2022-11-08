// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_EffectComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_EffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_EffectComponent();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	USceneComponent* GetEffectSystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void Spawn();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void Despawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ParticleSystem;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
