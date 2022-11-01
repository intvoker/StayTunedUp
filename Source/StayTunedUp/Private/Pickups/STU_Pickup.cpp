// Stay Tuned Up Game


#include "Pickups/STU_Pickup.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/STU_Character.h"

// Sets default values
ASTU_Pickup::ASTU_Pickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphereComponent");
	CollisionSphereComponent->InitSphereRadius(50.0f);
	CollisionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionSphereComponent);

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->SetupAttachment(GetRootComponent());
}

void ASTU_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	DoPickup(Cast<ASTU_Character>(OtherActor));
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

void ASTU_Pickup::DoPickup(ASTU_Character* STU_Character)
{
	if (!bActive || !STU_Character || !CanUsePickup(STU_Character))
		return;

	UsePickup(STU_Character);

	Despawn();

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::Respawn, RespawnTime);
}

bool ASTU_Pickup::CanUsePickup(ASTU_Character* STU_Character)
{
	return false;
}

void ASTU_Pickup::UsePickup(ASTU_Character* STU_Character)
{
}

// Called every frame
void ASTU_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTU_Pickup::Respawn()
{
	bActive = true;

	if (ParticleSystem)
	{
		ParticleSystemComponent->SetTemplate(ParticleSystem);
		ParticleSystemComponent->ActivateSystem();
	}

	GetWorld()->GetTimerManager().SetTimer(CheckOverlappingActorsTimerHandle, this, &ThisClass::CheckOverlappingActors,
	                                       CheckOverlappingActorsTime, true);
}

void ASTU_Pickup::Despawn()
{
	bActive = false;

	ParticleSystemComponent->DeactivateSystem();

	GetWorld()->GetTimerManager().ClearTimer(CheckOverlappingActorsTimerHandle);
}

void ASTU_Pickup::CheckOverlappingActors()
{
	TSet<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, ASTU_Character::StaticClass());

	for (AActor* OverlappingActor : OverlappingActors)
	{
		DoPickup(Cast<ASTU_Character>(OverlappingActor));
	}
}
