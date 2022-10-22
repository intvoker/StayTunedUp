// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_FallDamageComponent.generated.h"

USTRUCT(BlueprintType)
struct FSTU_Range
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Min = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max = 0.0f;

	TRange<float> MakeRange() const { return TRange<float>(Min, Max); }
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_FallDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_FallDamageComponent();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FSTU_Range FallDamageVelocity = FSTU_Range{900.0f, 1200.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FSTU_Range FallDamage = FSTU_Range{10.0f, 100.0f};

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnLandedCallback(const FHitResult& Hit);
};
