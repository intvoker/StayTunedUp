// Stay Tuned Up Game


#include "Weapons/STUBaseWeapon.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}
