// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_RespawnComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_RespawnComponent();

	void StartRespawn(int32 RespawnTime);

	bool IsRespawning() const;

	int32 GetRespawnRemainingSeconds() const { return RespawnRemainingSeconds; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	float UpdateRespawnTime = 1.0f;

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	int32 RespawnRemainingSeconds = 0;
	FTimerHandle UpdateRespawnTimerHandle;

	void UpdateRespawn();
};
