// Stay Tuned Up Game


#include "Pickups/STU_Pickup.h"

#include "Components/SphereComponent.h"
#include "Components/STU_EffectComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASTU_Pickup::ASTU_Pickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphereComponent");
	CollisionSphereComponent->InitSphereRadius(50.0f);
	CollisionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionSphereComponent);

	EffectComponent = CreateDefaultSubobject<USTU_EffectComponent>("EffectComponent");
	EffectComponent->SetupEffectAttachment(GetRootComponent());
}

void ASTU_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	DoPickup(Cast<ACharacter>(OtherActor));
}

// Called when the game starts or when spawned
void ASTU_Pickup::BeginPlay()
{
	Super::BeginPlay();

	Respawn();
}

void ASTU_Pickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(CheckOverlappingActorsTimerHandle);
}

void ASTU_Pickup::DoPickup(ACharacter* Character)
{
	if (!bActive || !Character || !TryUsePickup(Character))
		return;

	Despawn();

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::Respawn, RespawnTime);
}

bool ASTU_Pickup::TryUsePickup(ACharacter* Character)
{
	return false;
}

void ASTU_Pickup::Respawn()
{
	bActive = true;

	EffectComponent->Spawn();

	GetWorld()->GetTimerManager().SetTimer(CheckOverlappingActorsTimerHandle, this, &ThisClass::CheckOverlappingActors,
	                                       CheckOverlappingActorsTime, true);
}

void ASTU_Pickup::Despawn()
{
	bActive = false;

	EffectComponent->Despawn();

	GetWorld()->GetTimerManager().ClearTimer(CheckOverlappingActorsTimerHandle);
}

void ASTU_Pickup::CheckOverlappingActors()
{
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

	for (AActor* OverlappingActor : OverlappingActors)
	{
		DoPickup(Cast<ACharacter>(OverlappingActor));
	}
}
