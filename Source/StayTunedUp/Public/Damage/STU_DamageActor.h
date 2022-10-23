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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	int32 Segments = 24;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FColor Color = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	bool bDoFullDamage = false;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
