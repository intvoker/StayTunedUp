// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STU_HealthComponent.h"
#include "Components/STU_RespawnComponent.h"
#include "Components/STU_WeaponComponent.h"
#include "Player/STU_PlayerState.h"
#include "STU_GameModeBase.h"
#include "UI/STU_PlayerStateWidget.h"
#include "Weapons/STU_Weapon.h"

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

	if (STU_GameModeBase->IsNoTimeLimit())
		return FText::GetEmpty();

	const auto RoundInfo = FString::Printf(
		TEXT("Round: %d / %d. Remaining %d seconds."), STU_GameModeBase->GetCurrentRoundIndex(),
		STU_GameModeBase->GetNumberOfRounds(), STU_GameModeBase->GetCurrentRoundRemainingSeconds());

	return FText::FromString(RoundInfo);
}

void USTU_PlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto PlayerController = GetOwningPlayer())
	{
		PlayerController->GetOnNewPawnNotifier().AddUObject(this, &ThisClass::HandleOnNewPawn);
		HandleOnNewPawn(GetOwningPlayerPawn());
	}
}

void USTU_PlayerHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PlayerStateWidget)
	{
		PlayerStateWidget->SetPlayerState(GetPlayerState());
	}
}

ASTU_PlayerState* USTU_PlayerHUDWidget::GetPlayerState() const
{
	const auto PlayerController = GetOwningPlayer();
	if (!PlayerController)
		return nullptr;

	return Cast<ASTU_PlayerState>(PlayerController->PlayerState);
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

void USTU_PlayerHUDWidget::HandleOnNewPawn(APawn* NewPawn)
{
	if (const auto HealthComponent = GetPawnComponent<USTU_HealthComponent>())
	{
		if (!HealthComponent->OnHealthChanged.IsAlreadyBound(this, &ThisClass::HandleOnHealthChanged))
		{
			HealthComponent->OnHealthChanged.AddDynamic(this, &ThisClass::HandleOnHealthChanged);
		}
	}
}

void USTU_PlayerHUDWidget::HandleOnHealthChanged(float Health, float HealthDelta)
{
	if (HealthDelta >= 0.0f)
		return;

	if (!DamageAnimation && !IsAnimationPlaying(DamageAnimation))
		return;

	PlayAnimation(DamageAnimation);
}
