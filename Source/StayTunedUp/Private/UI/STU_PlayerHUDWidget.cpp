// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_RespawnComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "STU_GameModeBase.h"
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

bool USTU_PlayerHUDWidget::IsAlive()
{
	const auto HealthComponent = GetPawnComponent<USTU_HealthComponent>();
	if (!HealthComponent)
		return false;

	return !HealthComponent->IsDead();
}

ESlateVisibility USTU_PlayerHUDWidget::IsAliveVisible()
{
	return IsAlive() ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

float USTU_PlayerHUDWidget::GetHealthPercent()
{
	const auto HealthComponent = GetPawnComponent<USTU_HealthComponent>();
	if (!HealthComponent)
		return 0.0f;

	return HealthComponent->GetHealthPercent();
}

FSlateBrush USTU_PlayerHUDWidget::GetCurrentWeaponCrosshairIcon()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FSlateBrush();

	return CreateBrush(Weapon->GetWeaponUIData().CrosshairIcon);
}

FSlateBrush USTU_PlayerHUDWidget::GetCurrentWeaponMainIcon()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FSlateBrush();

	return CreateBrush(Weapon->GetWeaponUIData().MainIcon);
}

FText USTU_PlayerHUDWidget::GetCurrentWeaponAmmoInfo()
{
	const auto Weapon = GetCurrentWeapon();
	if (!Weapon)
		return FText::GetEmpty();

	const auto AmmoData = Weapon->GetAmmoData();

	const auto AmmoInfo = FString::Printf(TEXT("Ammo: %d / %s"), AmmoData.Rounds,
	                                      *(AmmoData.bInfinite ? "Infinite" : FString::FromInt(AmmoData.Clips)));

	return FText::FromString(AmmoInfo);
}

bool USTU_PlayerHUDWidget::IsSpectating()
{
	const auto PlayerController = GetOwningPlayer();

	return PlayerController && PlayerController->IsInState(NAME_Spectating);
}

ESlateVisibility USTU_PlayerHUDWidget::IsSpectatingVisible()
{
	return IsSpectating() ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

FText USTU_PlayerHUDWidget::GetSpectatingInfo()
{
	const auto RespawnComponent = GetControllerComponent<USTU_RespawnComponent>();
	if (!RespawnComponent || !RespawnComponent->IsRespawning())
		return FText::GetEmpty();

	const auto SpectatingInfo = FString::Printf(
		TEXT("Respawning in %d seconds."), RespawnComponent->GetRespawnRemainingSeconds());

	return FText::FromString(SpectatingInfo);
}

FText USTU_PlayerHUDWidget::GetRoundInfo()
{
	const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>();
	if (!STU_GameModeBase)
		return FText::GetEmpty();

	const auto RoundInfo = FString::Printf(
		TEXT("Round: %d/%d. Remaining %d seconds."), STU_GameModeBase->GetCurrentRoundIndex(),
		STU_GameModeBase->GetNumberOfRounds(), STU_GameModeBase->GetCurrentRoundRemainingSeconds());

	return FText::FromString(RoundInfo);
}

ASTU_Weapon* USTU_PlayerHUDWidget::GetCurrentWeapon()
{
	const auto WeaponComponent = GetPawnComponent<USTU_WeaponComponent>();
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

void USTU_PlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	if (const auto HealthComponent = GetPawnComponent<USTU_HealthComponent>())
	{
		if (!HealthComponent->OnHealthChanged.IsAlreadyBound(this, &ThisClass::OnHealthChanged))
		{
			HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
		}
	}
}

void USTU_PlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta >= 0.0f)
		return;

	if (!DamageAnimation && !IsAnimationPlaying(DamageAnimation))
		return;

	PlayAnimation(DamageAnimation);
}
