// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PlayerHUDWidget.generated.h"

class ASTU_Weapon;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsAlive();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FSlateBrush GeCurrentWeaponCrosshairIcon();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FSlateBrush GeCurrentWeaponMainIcon();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GeCurrentWeaponAmmoInfo();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DamageAnimation;

private:
	template <typename T>
	T* GetComponent();

	ASTU_Weapon* GetCurrentWeapon();

	FSlateBrush CreateBrush(UTexture2D* Icon);

	UFUNCTION()
	void OnHealthChanged(float Health, float HealthDelta);
};

template <typename T>
T* USTU_PlayerHUDWidget::GetComponent()
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
		return nullptr;

	return PlayerPawn->FindComponentByClass<T>();
}
