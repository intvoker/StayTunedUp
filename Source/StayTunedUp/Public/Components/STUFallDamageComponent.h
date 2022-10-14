// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFallDamageComponent.generated.h"

USTRUCT(BlueprintType)
struct FSTURange
{
	GENERATED_USTRUCT_BODY()

	FSTURange()
	{
	}

	FSTURange(const float MinParam, const float MaxParam):
		Min(MinParam), Max(MaxParam)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Min = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max = 0.0f;

	TRange<float> MakeRange() const { return TRange<float>(Min, Max); }
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTUFallDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTUFallDamageComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FSTURange FallDamageVelocity = FSTURange(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FSTURange FallDamage = FSTURange(10.0f, 100.0f);

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnLandedCallback(const FHitResult& Hit);
};
