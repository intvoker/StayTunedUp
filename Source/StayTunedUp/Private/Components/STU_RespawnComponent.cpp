// Stay Tuned Up Game


#include "Components/STU_RespawnComponent.h"

#include "STU_GameModeBase.h"

// Sets default values for this component's properties
USTU_RespawnComponent::USTU_RespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USTU_RespawnComponent::StartRespawn(int32 RespawnTime)
{
	RespawnRemainingSeconds = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(UpdateRespawnTimerHandle, this, &ThisClass::UpdateRespawn, UpdateRespawnTime,
	                                       true);
}

bool USTU_RespawnComponent::IsRespawning() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(UpdateRespawnTimerHandle);
}

// Called when the game starts
void USTU_RespawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void USTU_RespawnComponent::UpdateRespawn()
{
	const auto Controller = Cast<AController>(GetOwner());
	if (!Controller)
		return;

	const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>();
	if (!STU_GameModeBase)
		return;

	RespawnRemainingSeconds -= UpdateRespawnTime;

	if (RespawnRemainingSeconds <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(UpdateRespawnTimerHandle);

		STU_GameModeBase->DoRespawn(Controller);
	}
}
