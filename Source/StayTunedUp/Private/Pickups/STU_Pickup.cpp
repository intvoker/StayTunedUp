// Stay Tuned Up Game


#include "Pickups/STU_Pickup.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

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

// Called when the game starts or when spawned
void ASTU_Pickup::BeginPlay()
{
	Super::BeginPlay();

	if (ParticleSystem)
	{
		ParticleSystemComponent->SetTemplate(ParticleSystem);
		ParticleSystemComponent->ActivateSystem();
	}
}

void ASTU_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Destroy();
}

// Called every frame
void ASTU_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
