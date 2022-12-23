// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_PlayerHUDWidget.generated.h"

class ASTU_PlayerState;
class ASTU_Weapon;
class USTU_PlayerStateWidget;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_PlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsAlive();

	UFUNCTION(BlueprintCallable, Category = "UI")
	ESlateVisibility IsAliveVisible();

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FSlateBrush GetCurrentWeaponCrosshairIcon();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FSlateBrush GetCurrentWeaponMainIcon();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetCurrentWeaponAmmoInfo();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool IsSpectating();

	UFUNCTION(BlueprintCallable, Category = "UI")
	ESlateVisibility IsSpectatingVisible();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetSpectatingInfo();

	UFUNCTION(BlueprintCallable, Category = "UI")
	FText GetRoundInfo();

protected:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DamageAnimation;

	UPROPERTY(meta = (BindWidget))
	USTU_PlayerStateWidget* PlayerStateWidget;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	template <typename T>
	T* GetControllerComponent();

	template <typename T>
	T* GetPawnComponent();

	ASTU_PlayerState* GetPlayerState() const;

	ASTU_Weapon* GetCurrentWeapon();

	FSlateBrush CreateBrush(UTexture2D* Icon);

	void OnNewPawn(APawn* NewPawn);

	UFUNCTION()
	void OnHealthChanged(float Health, float HealthDelta);
};

template <typename T>
T* USTU_PlayerHUDWidget::GetControllerComponent()
{
	const auto PlayerController = GetOwningPlayer();
	if (!PlayerController)
		return nullptr;

	return PlayerController->FindComponentByClass<T>();
}

template <typename T>
T* USTU_PlayerHUDWidget::GetPawnComponent()
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
		return nullptr;

	return PlayerPawn->FindComponentByClass<T>();
}
