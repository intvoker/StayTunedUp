// Stay Tuned Up Game


#include "Components/STU_WeaponEffectsComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USTU_WeaponEffectsComponent::USTU_WeaponEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USTU_WeaponEffectsComponent::PlayImpactEffect(const FHitResult& HitResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint,
	                                         HitResult.ImpactNormal.Rotation());
}

// Called when the game starts
void USTU_WeaponEffectsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USTU_WeaponEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
