// Stay Tuned Up Game


#include "Weapons/STUBaseWeapon.h"

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

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUBaseWeapon::MakeShot()
{
	FVector PlayerViewLocation;
	FVector PlayerViewDirection;
	GetPlayerViewPoint(PlayerViewLocation, PlayerViewDirection);

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	const FVector Start = PlayerViewLocation;
	const FVector End = Start + PlayerViewDirection * MaxRange;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), WeaponViewLocation, HitResult.ImpactPoint, FColor::Red, false, 5.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

		DealDamage(HitResult);
	}
	else
	{
		DrawDebugLine(GetWorld(), WeaponViewLocation, End, FColor::Blue, false, 5.0f);
		DrawDebugSphere(GetWorld(), End, 10.0f, 24, FColor::Blue, false, 5.0f);
	}
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
