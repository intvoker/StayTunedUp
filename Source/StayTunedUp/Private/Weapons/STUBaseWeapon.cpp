// Stay Tuned Up Game


#include "Weapons/STUBaseWeapon.h"

#include "Animations/STUAnimUtility.h"
#include "GameFramework/Character.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void ASTUBaseWeapon::Fire()
{
	MakeShot();
}

void ASTUBaseWeapon::StopFiring()
{
}

void ASTUBaseWeapon::OnOwnerDeath()
{
	STUAnimUtility::SetRagdoll(this, WeaponMesh);

	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUBaseWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASTUBaseWeapon::MakeShot()
{
	FVector PlayerViewLocation;
	FVector PlayerViewDirection;
	GetPlayerViewPoint(PlayerViewLocation, PlayerViewDirection);

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	FVector Start;
	FVector End;
	GetTraceData(PlayerViewLocation, PlayerViewDirection, Start, End);

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams);

	FVector TraceEnd = HitResult.bBlockingHit ? HitResult.ImpactPoint : End;
	ProcessShot(WeaponViewLocation, TraceEnd, HitResult);
}

void ASTUBaseWeapon::ProcessShot(FVector& TraceStart, FVector& TraceEnd, FHitResult& HitResult)
{
	DealDamage(HitResult);
}

void ASTUBaseWeapon::DealDamage(FHitResult& HitResult)
{
	const auto EnemyCharacter = Cast<ACharacter>(HitResult.GetActor());
	if (!EnemyCharacter)
		return;

	EnemyCharacter->TakeDamage(DamageAmount, FDamageEvent(), nullptr, GetOwner());
}

void ASTUBaseWeapon::GetPlayerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const auto PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (!PlayerCharacter)
		return;

	const auto PlayerController = PlayerCharacter->GetController<APlayerController>();
	if (!PlayerController)
		return;

	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(OutViewLocation, ViewRotation);
	OutViewDirection = ViewRotation.Vector();
}

void ASTUBaseWeapon::GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const FTransform MuzzleFlashSocketTransform = WeaponMesh->GetSocketTransform(MuzzleFlashSocketName);
	OutViewLocation = MuzzleFlashSocketTransform.GetLocation();
	OutViewDirection = MuzzleFlashSocketTransform.GetRotation().GetForwardVector();
}

void ASTUBaseWeapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}
