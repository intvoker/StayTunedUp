// Stay Tuned Up Game


#include "Components/STU_HealthComponent.h"

// Sets default values for this component's properties
USTU_HealthComponent::USTU_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool USTU_HealthComponent::TryAddHealth(float HealthAmount)
{
	if (IsMaxHealth() || IsDead())
		return false;

	SetHealth(Health + HealthAmount);

	return true;
}

// Called when the game starts
void USTU_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (const auto ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamage);
	}
}

void USTU_HealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void USTU_HealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void USTU_HealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                           AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead())
		return;

	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (bAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &ThisClass::OnHealTimer, HealUpdateTime, true,
		                                       HealDelay);
	}
}

void USTU_HealthComponent::OnHealTimer()
{
	SetHealth(Health + HealModifier);

	if (IsMaxHealth())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
