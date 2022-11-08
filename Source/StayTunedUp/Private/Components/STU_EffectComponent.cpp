// Stay Tuned Up Game


#include "Components/STU_EffectComponent.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
USTU_EffectComponent::USTU_EffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->bAutoActivate = false;
}

USceneComponent* USTU_EffectComponent::GetEffectSystemComponent() const
{
	return ParticleSystemComponent;
}

void USTU_EffectComponent::Spawn()
{
	if (ParticleSystem)
	{
		ParticleSystemComponent->SetTemplate(ParticleSystem);
		ParticleSystemComponent->ActivateSystem();
	}
}

void USTU_EffectComponent::Despawn()
{
	ParticleSystemComponent->DeactivateSystem();
}

// Called when the game starts
void USTU_EffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}
