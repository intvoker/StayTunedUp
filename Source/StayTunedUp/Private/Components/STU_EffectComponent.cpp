// Stay Tuned Up Game


#include "Components/STU_EffectComponent.h"

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values for this component's properties
USTU_EffectComponent::USTU_EffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleSystemComponent->bAutoActivate = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
}

void USTU_EffectComponent::SetupEffectAttachment(USceneComponent* InParent, FName InSocketName)
{
	ParticleSystemComponent->SetupAttachment(InParent, InSocketName);

	AudioComponent->SetupAttachment(InParent, InSocketName);
}

void USTU_EffectComponent::Spawn()
{
	ParticleSystemComponent->ActivateSystem();

	bRevertSoundBehavior ? AudioComponent->Stop() : AudioComponent->Play();
}

void USTU_EffectComponent::Despawn()
{
	ParticleSystemComponent->DeactivateSystem();

	if (bStopSoundOnDespawn)
	{
		bRevertSoundBehavior ? AudioComponent->Play() : AudioComponent->Stop();
	}
}

// Called when the game starts
void USTU_EffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ParticleSystem)
	{
		ParticleSystemComponent->SetTemplate(ParticleSystem);
	}

	if (SoundCue)
	{
		AudioComponent->SetSound(SoundCue);
	}
}
