// Stay Tuned Up Game


#include "Components/STU_AIPerceptionComponent.h"

#include "Components/STU_HealthComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "STU_GameModeBase.h"

AActor* USTU_AIPerceptionComponent::FindNearestAliveEnemyActor() const
{
	const auto Controller = Cast<AController>(GetOwner());
	if (!Controller)
		return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
		return nullptr;

	TArray<AActor*> AllPerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), AllPerceivedActors);
	GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), AllPerceivedActors);

	TArray<AActor*> PerceivedActors;
	for (const auto PerceivedActor : AllPerceivedActors)
	{
		if (!PerceivedActor->IsA(ACharacter::StaticClass()))
			continue;

		PerceivedActors.AddUnique(PerceivedActor);
	}

	float MinDistance = MAX_FLT;
	AActor* EnemyActor = nullptr;
	for (const auto PerceivedActor : PerceivedActors)
	{
		const auto HealthComponent = PerceivedActor->FindComponentByClass<USTU_HealthComponent>();
		if (!HealthComponent || HealthComponent->IsDead())
			continue;

		if (!CanKill(PerceivedActor))
			continue;

		const auto Distance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			EnemyActor = PerceivedActor;
		}
	}

	return EnemyActor;
}

bool USTU_AIPerceptionComponent::CanKill(const AActor* VictimActor) const
{
	const auto Controller = Cast<AController>(GetOwner());
	if (!Controller)
		return false;

	const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>();
	if (!STU_GameModeBase)
		return false;

	const auto VictimPawn = Cast<APawn>(VictimActor);
	if (!VictimPawn)
		return false;

	return STU_GameModeBase->CanKill(Controller, VictimPawn->GetController());
}
