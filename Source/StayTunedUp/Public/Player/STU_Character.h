// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STU_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float LifeSpan = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MaterialColorName = "Paint Color";

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

	UFUNCTION()
	virtual void OnHealthChanged(float Health, float HealthDelta);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;
	virtual void TurnOff() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMovingForward() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetPlayerColor(const FLinearColor& Color);

private:
	bool bPressedRun = false;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	void Run();
	void StopRunning();

	void SetComponentFacePlayer(USceneComponent* SceneComponent) const;
};
