// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
UCLASS()
class STAYTUNEDUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTUProjectile();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
	USphereComponent* CollisionSphereComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
