// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Brushes/SlateImageBrush.h"
#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Weapons/STU_Weapon.h"

float USTU_PlayerHUDWidget::GetHealthPercent()
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
		return 0.f;

	const auto ActorComponent = PlayerPawn->FindComponentByClass(USTU_HealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTU_HealthComponent>(ActorComponent);
	if (!HealthComponent)
		return 0.f;

	return HealthComponent->GetHealthPercent();
}

FSlateBrush USTU_PlayerHUDWidget::GeCurrentWeaponCrosshairIcon()
{
	const auto PlayerPawn = GetOwningPlayerPawn();
	if (!PlayerPawn)
		return FSlateBrush();

	const auto ActorComponent = PlayerPawn->FindComponentByClass(USTU_WeaponComponent::StaticClass());
	const auto WeaponComponent = Cast<USTU_WeaponComponent>(ActorComponent);
	if (!WeaponComponent)
		return FSlateBrush();

	const auto Weapon = WeaponComponent->GetCurrentWeapon();
	if (!Weapon)
		return FSlateBrush();

	const auto CrosshairIcon = Weapon->GetWeaponUIData().CrosshairIcon;
	if (!CrosshairIcon)
		return FSlateBrush();

	return FSlateImageBrush(CrosshairIcon, FVector2d(CrosshairIcon->GetSizeX(), CrosshairIcon->GetSizeY()));
}
