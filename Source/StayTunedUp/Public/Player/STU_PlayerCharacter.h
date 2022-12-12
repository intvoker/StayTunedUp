// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_PlayerCharacter : public ASTU_Character
{
	GENERATED_BODY()

public:
	ASTU_PlayerCharacter(const FObjectInitializer& ObjectInitializer);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	virtual void OnDeath() override;

	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	bool bPressedRun = false;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	void Run();
	void StopRunning();
};
