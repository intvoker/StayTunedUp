// Stay Tuned Up Game


#include "Damage/STUDamageActor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASTUDamageActor::ASTUDamageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASTUDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASTUDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, Segments, Color);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr,
	                                    bDoFullDamage);
}
