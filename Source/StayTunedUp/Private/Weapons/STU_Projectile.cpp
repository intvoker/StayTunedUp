// Stay Tuned Up Game


#include "Weapons/STU_Projectile.h"

#include "Components/SphereComponent.h"
#include "Components/STU_EffectComponent.h"
#include "Components/STU_WeaponEffectsComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASTU_Projectile::ASTU_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>("CollisionSphereComponent");
	CollisionSphereComponent->InitSphereRadius(5.0f);
	CollisionSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CollisionSphereComponent->bReturnMaterialOnMove = true;
	//CollisionSphereComponent->SetEnableGravity(false);
	//CollisionSphereComponent->SetSimulatePhysics(true);
	SetRootComponent(CollisionSphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	EffectComponent = CreateDefaultSubobject<USTU_EffectComponent>("EffectComponent");
	EffectComponent->SetupEffectAttachment(GetRootComponent());

	WeaponEffectsComponent = CreateDefaultSubobject<USTU_WeaponEffectsComponent>("WeaponEffectsComponent");
}

// Called when the game starts or when spawned
void ASTU_Projectile::BeginPlay()
{
	Super::BeginPlay();

	EffectComponent->Spawn();

	ProjectileMovementComponent->Velocity = ProjectileDirection * ProjectileMovementComponent->InitialSpeed;
	CollisionSphereComponent->OnComponentHit.AddDynamic(this, &ThisClass::HandleOnComponentHitCollision);
	//UE_LOG(LogTemp, Warning, TEXT("ProjectileDirection: %s"), *ProjectileDirection.ToString());

	SetLifeSpan(LifeSpan);
}

void ASTU_Projectile::HandleOnComponentHitCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                                    const FHitResult& Hit)
{
	EffectComponent->Despawn();

	WeaponEffectsComponent->SpawnImpactEffect(Hit);

	const auto Controller = GetOwner() ? GetOwner()->GetInstigatorController() : nullptr;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, nullptr, {}, this,
	                                    Controller, bDoFullDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);

	Destroy();
}
