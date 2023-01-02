// Stay Tuned Up Game


#include "AI/STU_AIController.h"

#include "AI/STU_AICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STU_AIPerceptionComponent.h"
#include "Components/STU_RespawnComponent.h"

ASTU_AIController::ASTU_AIController()
{
	STU_AIPerceptionComponent = CreateDefaultSubobject<USTU_AIPerceptionComponent>("STU_AIPerceptionComponent");

	SetPerceptionComponent(*STU_AIPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");

	bWantsPlayerState = true;
}

void ASTU_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
		return;

	const auto EnemyActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(EnemyActorKeyName));
	SetFocus(EnemyActor);
}

void ASTU_AIController::GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	GetActorEyesViewPoint(OutLocation, OutRotation);
}

void ASTU_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto STU_AICharacter = Cast<ASTU_AICharacter>(InPawn))
	{
		RunBehaviorTree(STU_AICharacter->BehaviorTree);
	}
}

void ASTU_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}
