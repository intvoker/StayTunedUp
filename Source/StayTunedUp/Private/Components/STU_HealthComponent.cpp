// Stay Tuned Up Game


#include "Components/STU_HealthComponent.h"

#include "Perception/AISense_Damage.h"
#include "STU_GameModeBase.h"

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
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::HandleOnTakeAnyDamage);
	}
}

void USTU_HealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void USTU_HealthComponent::SetHealth(float NewHealth)
{
	NewHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NewHealth - Health;

	Health = NewHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

void USTU_HealthComponent::HandleOnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                                 AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead())
		return;

	SetHealth(Health - Damage);
	Damaged(InstigatedBy, Damage);
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

	if (IsDead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	else if (bAutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &ThisClass::Heal, HealUpdateTime, true,
		                                       HealDelay);
	}
}

void USTU_HealthComponent::Heal()
{
	SetHealth(Health + HealModifier);

	if (IsMaxHealth())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTU_HealthComponent::Damaged(const AController* InstigatedBy, float Damage) const
{
	if (!InstigatedBy)
		return;

	const auto DamageCauser = InstigatedBy->GetPawn();
	if (!DamageCauser)
		return;

	const auto ComponentOwner = GetOwner();
	if (!ComponentOwner)
		return;

	UAISense_Damage::ReportDamageEvent(GetWorld(), ComponentOwner, DamageCauser, Damage,
	                                   DamageCauser->GetActorLocation(), ComponentOwner->GetActorLocation());
}

void USTU_HealthComponent::Killed(const AController* Killer) const
{
	const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>();
	if (!STU_GameModeBase)
		return;

	const auto Pawn = Cast<APawn>(GetOwner());
	if (!Pawn)
		return;

	STU_GameModeBase->Killed(Killer, Pawn->Controller);
}
