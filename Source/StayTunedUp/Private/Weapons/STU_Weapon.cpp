// Stay Tuned Up Game


#include "Weapons/STU_Weapon.h"

#include "Animations/STU_AnimUtility.h"
#include "Components/STU_EffectComponent.h"
#include "Components/STU_WeaponEffectsComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASTU_Weapon::ASTU_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetRootComponent());

	MuzzleEffectComponent = CreateDefaultSubobject<USTU_EffectComponent>("MuzzleEffectComponent");
	MuzzleEffectComponent->GetEffectSystemComponent()->SetupAttachment(WeaponMesh, MuzzleFlashSocketName);

	WeaponEffectsComponent = CreateDefaultSubobject<USTU_WeaponEffectsComponent>("WeaponEffectsComponent");
}

void ASTU_Weapon::Fire()
{
	MakeShot();
}

void ASTU_Weapon::StopFiring()
{
	MuzzleEffectComponent->Despawn();
}

bool ASTU_Weapon::CanUseClip() const
{
	return CurrentAmmo.Clips > 0;
}

void ASTU_Weapon::UseClip()
{
	if (!CanUseClip())
		return;

	CurrentAmmo.Rounds = DefaultAmmo.Rounds;

	if (!CurrentAmmo.bInfinite)
	{
		CurrentAmmo.Clips--;
	}
}

FText ASTU_Weapon::GetAmmoInfo()
{
	FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Rounds) + " / ";
	AmmoInfo += CurrentAmmo.bInfinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	return FText::FromString(AmmoInfo);
}

void ASTU_Weapon::OnOwnerDeath()
{
	STU_AnimUtility::SetRagdoll(this, WeaponMesh);

	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	SetLifeSpan(LifeSpan);
}

bool ASTU_Weapon::TryAddClip(float ClipAmount)
{
	if (CurrentAmmo.bInfinite)
		return false;

	if (CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Rounds == DefaultAmmo.Rounds)
		return false;

	SetClips(CurrentAmmo.Clips + ClipAmount);

	return true;
}

// Called when the game starts or when spawned
void ASTU_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;
}

void ASTU_Weapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASTU_Weapon::MakeShot()
{
	if (!CanUseRound())
	{
		StopFiring();
		return;
	}

	MuzzleEffectComponent->Spawn();

	FVector PlayerViewLocation;
	FVector PlayerViewDirection;
	GetPlayerViewPoint(PlayerViewLocation, PlayerViewDirection);

	FVector WeaponViewLocation;
	FVector WeaponViewDirection;
	GetWeaponViewPoint(WeaponViewLocation, WeaponViewDirection);

	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(PlayerViewLocation, PlayerViewDirection, TraceStart, TraceEnd);

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	CollisionQueryParams.bReturnPhysicalMaterial = true;

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

	UseRound();

	if (HitResult.bBlockingHit)
	{
		TraceEnd = HitResult.ImpactPoint;
	}

	WeaponEffectsComponent->SpawnTraceEffect(WeaponViewLocation, TraceEnd);

	ProcessShot(WeaponViewLocation, TraceEnd, HitResult);
}

void ASTU_Weapon::ProcessShot(FVector& ShotStart, FVector& ShotEnd, FHitResult& HitResult)
{
	/*
	const auto DebugColor = HitResult.bBlockingHit ? FColor::Red : FColor::Blue;
	DrawDebugLine(GetWorld(), ShotStart, ShotEnd, DebugColor, false, 5.0f);
	DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, DebugColor, false, 5.0f);
	*/
}

void ASTU_Weapon::GetPlayerViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const auto Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (!Character->IsPlayerControlled())
	{
		GetWeaponViewPoint(OutViewLocation, OutViewDirection);
		return;
	}

	const auto PlayerController = Character->GetController<APlayerController>();
	if (!PlayerController)
		return;

	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(OutViewLocation, ViewRotation);
	OutViewDirection = ViewRotation.Vector();
}

void ASTU_Weapon::GetWeaponViewPoint(FVector& OutViewLocation, FVector& OutViewDirection)
{
	const FTransform MuzzleFlashSocketTransform = WeaponMesh->GetSocketTransform(MuzzleFlashSocketName);
	OutViewLocation = MuzzleFlashSocketTransform.GetLocation();
	OutViewDirection = MuzzleFlashSocketTransform.GetRotation().GetForwardVector();
}

void ASTU_Weapon::GetTraceData(FVector& Location, FVector& Direction, FVector& OutTraceStart, FVector& OutTraceEnd)
{
	OutTraceStart = Location;
	OutTraceEnd = OutTraceStart + Direction * MaxRange;
}

bool ASTU_Weapon::CanUseRound() const
{
	return CurrentAmmo.Rounds > 0;
}

void ASTU_Weapon::UseRound()
{
	if (!CanUseRound())
		return;

	CurrentAmmo.Rounds--;

	if (!CanUseRound())
	{
		OnClipEmpty.Broadcast(this);
	}
}

void ASTU_Weapon::SetClips(float NewClips)
{
	CurrentAmmo.Clips = FMath::Clamp(NewClips, 0.0f, DefaultAmmo.Clips);

	if (NewClips > DefaultAmmo.Clips)
	{
		CurrentAmmo.Rounds = DefaultAmmo.Rounds;
	}

	if (!CanUseRound())
	{
		OnClipEmpty.Broadcast(this);
	}
}
