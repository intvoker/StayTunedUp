// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Pickup.generated.h"

class USphereComponent;
class USTU_EffectComponent;

UCLASS()
class STAYTUNEDUP_API ASTU_Pickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTU_Pickup();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	bool IsActive() const { return bActive; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CollisionSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_EffectComponent* EffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	float CheckOverlappingActorsTime = 1.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void DoPickup(ACharacter* Character);

	virtual bool TryUsePickup(ACharacter* Character);

private:
	bool bActive = false;

	FTimerHandle RespawnTimerHandle;
	void Respawn();
	void Despawn();

	FTimerHandle CheckOverlappingActorsTimerHandle;
	void CheckOverlappingActors();
};
