// Stay Tuned Up Game


#include "Damage/STU_DamageActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASTU_DamageActor::ASTU_DamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASTU_DamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASTU_DamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, Segments, Color);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr,
	                                    bDoFullDamage);
}
