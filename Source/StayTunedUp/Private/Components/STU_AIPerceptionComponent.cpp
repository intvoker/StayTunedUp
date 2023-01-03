// Stay Tuned Up Game


#include "Components/STU_AIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STU_HealthComponent.h"
#include "GameFramework/Character.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "STU_GameModeBase.h"

AActor* USTU_AIPerceptionComponent::FindNearestAliveEnemyActor() const
{
	const auto AIController = Cast<AAIController>(GetOwner());
	if (!AIController)
		return nullptr;

	const auto Pawn = AIController->GetPawn();
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
