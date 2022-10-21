// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STU_Character.generated.h"

class ASTU_Weapon;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_FallDamageComponent* FallDamageComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_WeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 10.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsMovingForward() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

private:
	bool bPressedRun = false;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	void Run();
	void StopRunning();

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnHealthChanged(float Health);
};
