// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Weapons/STU_Weapon.h"

float USTU_PlayerHUDWidget::GetHealthPercent()
{
	const auto HealthComponent = GetComponent<USTU_HealthComponent>();
	if (!HealthComponent)
		return 0.f;

	return HealthComponent->GetHealthPercent();
}

ASTU_Weapon* USTU_PlayerHUDWidget::GetCurrentWeapon()
{
	const auto WeaponComponent = GetComponent<USTU_WeaponComponent>();
	if (!WeaponComponent)
		return nullptr;

	return WeaponComponent->GetCurrentWeapon();
}

FSlateBrush USTU_PlayerHUDWidget::CreateBrush(UTexture2D* Icon)
{
	auto Brush = FSlateBrush();
	if (!Icon)
		return Brush;

	Brush.SetResourceObject(Icon);
	Brush.ImageSize = FVector2D(Icon->GetSizeX(), Icon->GetSizeY());
	return Brush;
}

FSlateBrush USTU_PlayerHUDWidget::GeCurrentWeaponCrosshairIcon()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FSlateBrush();

	return CreateBrush(Weapon->GetWeaponUIData().CrosshairIcon);
}

FSlateBrush USTU_PlayerHUDWidget::GeCurrentWeaponMainIcon()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FSlateBrush();

	return CreateBrush(Weapon->GetWeaponUIData().MainIcon);
}

FText USTU_PlayerHUDWidget::GeCurrentWeaponAmmoInfo()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FText::GetEmpty();

	return Weapon->GetAmmoInfo();
}
