// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_DamageActor.generated.h"

UCLASS()
class STAYTUNEDUP_API ASTU_DamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASTU_DamageActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Segments = 24;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDoFullDamage = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
