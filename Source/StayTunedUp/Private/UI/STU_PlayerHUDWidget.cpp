// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Weapons/STU_Weapon.h"

bool USTU_PlayerHUDWidget::Initialize()
{
	if (const auto PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().AddUObject(this, &ThisClass::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}

	return Super::Initialize();
}

float USTU_PlayerHUDWidget::GetHealthPercent()
{
	const auto HealthComponent = GetComponent<USTU_HealthComponent>();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTU_PlayerHUDWidget::IsAlive()
{
	const auto HealthComponent = GetComponent<USTU_HealthComponent>();
	if (!HealthComponent)
		return false;

	return !HealthComponent->IsDead();
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

	return FText::FromString(Weapon->GetAmmoInfo());
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

void USTU_PlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta >= 0.0f)
		return;

	if (!DamageAnimation && !IsAnimationPlaying(DamageAnimation))
		return;

	PlayAnimation(DamageAnimation);
}

void USTU_PlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	if (const auto HealthComponent = GetComponent<USTU_HealthComponent>())
	{
		if (!HealthComponent->OnHealthChanged.IsAlreadyBound(this, &ThisClass::OnHealthChanged))
		{
			HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
		}
	}
}
