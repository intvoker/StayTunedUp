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

void USTU_WeaponEffectsComponent::SpawnImpactEffect(const FHitResult& HitResult)
{
	auto ImpactData = DefaultImpactData;

	if (HitResult.PhysMaterial.IsValid())
	{
		if (const auto PhysMaterial = HitResult.PhysMaterial.Get(); ImpactDataMap.Contains(PhysMaterial))
		{
			ImpactData = ImpactDataMap[PhysMaterial];
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactData.Effect, HitResult.ImpactPoint,
	                                         HitResult.ImpactNormal.Rotation());

	if (ImpactData.DecalData.Material)
	{
		FRotator RandomDecalRotation = HitResult.ImpactNormal.Rotation();
		RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

		UGameplayStatics::SpawnDecalAttached(ImpactData.DecalData.Material, ImpactData.DecalData.Size,
		                                     HitResult.Component.Get(), HitResult.BoneName, HitResult.ImpactPoint,
		                                     RandomDecalRotation, EAttachLocation::KeepWorldPosition,
		                                     ImpactData.DecalData.LifeSpan);
	}
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
