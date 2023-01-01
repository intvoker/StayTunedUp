// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Player/STU_Character.h"
#include "STU_PlayerCharacter.generated.h"

class UCameraComponent;
class USphereComponent;
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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* CameraCollisionSphereComponent;

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	virtual void OnHealthChanged(float Health, float HealthDelta) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                   const FHitResult& SweepResult);

	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckCameraOverlap() const;
};
