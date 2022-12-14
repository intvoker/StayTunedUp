// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChangedSignature, float, Health, float, HealthDelta);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STAYTUNEDUP_API USTU_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USTU_HealthComponent();

	FDeathSignature OnDeath;
	FHealthChangedSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsMaxHealth() const { return FMath::IsNearlyEqual(Health, MaxHealth); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool TryAddHealth(float HealthAmount);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool bAutoHeal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "bAutoHeal"))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "bAutoHeal"))
	float HealDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "bAutoHeal"))
	float HealModifier = 1.0f;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	float Health = 0.0f;

	FTimerHandle HealTimerHandle;

	void SetHealth(float NewHealth);

	UFUNCTION()
	void HandleOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	                           AController* InstigatedBy, AActor* DamageCauser);

	void Heal();

	bool CanDamage(const AController* Killer) const;

	void Damaged(const AController* InstigatedBy, float Damage) const;
	void Killed(const AController* Killer) const;
};
