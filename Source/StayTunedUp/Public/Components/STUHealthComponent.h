// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTUHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health", meta=(ClampMin="0.0", ClampMax="1000.0"))
	float MaxHealth = 100.0f;

private:
	UPROPERTY()
	float Health = 0.0f;
};
