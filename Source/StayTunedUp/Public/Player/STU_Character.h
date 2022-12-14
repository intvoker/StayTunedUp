// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STU_Character.generated.h"

class USoundCue;
class USTU_FallDamageComponent;
class USTU_HealthComponent;
class USTU_WeaponComponent;
class UTextRenderComponent;

UCLASS()
class STAYTUNEDUP_API ASTU_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTU_Character(const FObjectInitializer& ObjectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;
	virtual void TurnOff() override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMovingForward() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Run();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopRunning();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetPlayerColor(const FLinearColor& Color);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_FallDamageComponent* FallDamageComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USTU_WeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	TSubclassOf<UCameraShakeBase> DamageCameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundCue* DeathSound;

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float LifeSpan = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MaterialColorName = "Paint Color";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Running",
		meta = (ClampMin = "0.0", ClampMax = "30.0"))
	float MaxRunAngle = 30.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void HandleOnDeath();

	UFUNCTION()
	virtual void HandleOnHealthChanged(float Health, float HealthDelta);

private:
	bool bPressedRun = false;

	UFUNCTION()
	void HandleOnCharacterMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

	void SetComponentFacePlayer(USceneComponent* SceneComponent) const;
};
