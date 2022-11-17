// Stay Tuned Up Game


#include "AI/Services/STU_FireBTService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"

USTU_FireBTService::USTU_FireBTService()
{
	NodeName = "Fire";
}

void USTU_FireBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	const auto AIController = OwnerComp.GetAIOwner();
	if (!AIController)
		return;

	const auto Pawn = AIController->GetPawn();
	if (!Pawn)
		return;

	const auto HealthComponent = Pawn->FindComponentByClass<USTU_HealthComponent>();
	if (!HealthComponent || HealthComponent->IsDead())
		return;

	const auto WeaponComponent = Pawn->FindComponentByClass<USTU_WeaponComponent>();
	if (!WeaponComponent)
		return;

	const auto EnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName));
	EnemyActor ? WeaponComponent->Fire() : WeaponComponent->StopFiring();
}
