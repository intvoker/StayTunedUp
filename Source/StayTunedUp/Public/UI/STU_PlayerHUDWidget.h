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
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FSlateBrush GeCurrentWeaponCrosshairIcon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FSlateBrush GeCurrentWeaponMainIcon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	FText GeCurrentWeaponAmmoInfo();

private:
	template <typename T>
	T* GetComponent();

	ASTU_Weapon* GetCurrentWeapon();
	FSlateBrush CreateBrush(UTexture2D* Icon);
};

template <typename T>
T* USTU_PlayerHUDWidget::GetComponent()
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
		return nullptr;

	const auto ActorComponent = PlayerPawn->FindComponentByClass(T::StaticClass());
	return Cast<T>(ActorComponent);
}
