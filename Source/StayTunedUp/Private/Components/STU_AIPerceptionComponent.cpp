// Stay Tuned Up Game


#include "Components/STU_AIPerceptionComponent.h"

#include "AIController.h"
#include "Components/STU_HealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTU_AIPerceptionComponent::FindNearestAliveActor()
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
	AActor* NearestActor = nullptr;
	for (const auto PerceivedActor : PerceivedActors)
	{
		const auto HealthComponent = PerceivedActor->FindComponentByClass<USTU_HealthComponent>();
		if (!HealthComponent || HealthComponent->IsDead())
		{
			continue;
		}

		const auto Distance = (PerceivedActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			NearestActor = PerceivedActor;
		}
	}

	return NearestActor;
}
