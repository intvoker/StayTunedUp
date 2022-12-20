// Stay Tuned Up Game


#include "Components/STU_AIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STU_HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/STU_Character.h"
#include "STU_GameModeBase.h"

AActor* USTU_AIPerceptionComponent::FindNearestAliveEnemyActor() const
{
	const auto AIController = Cast<AAIController>(GetOwner());
	if (!AIController)
		return nullptr;

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
		return nullptr;

	TArray<AActor*> PerceivedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

	float MinDistance = MAX_FLT;
	AActor* EnemyActor = nullptr;
	for (const auto PerceivedActor : PerceivedActors)
	{
		if (!PerceivedActor->IsA(ASTU_Character::StaticClass()))
			continue;

		const auto HealthComponent = PerceivedActor->FindComponentByClass<USTU_HealthComponent>();
		if (!HealthComponent || HealthComponent->IsDead())
			continue;

		const auto PerceivedPawn = Cast<APawn>(PerceivedActor);
		if (!PerceivedPawn)
			continue;

		const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>();
		if (!STU_GameModeBase)
			continue;

		if (!STU_GameModeBase->AreEnemies(Pawn->Controller, PerceivedPawn->Controller))
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
