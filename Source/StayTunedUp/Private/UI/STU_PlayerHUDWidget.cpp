// Stay Tuned Up Game


#include "UI/STU_PlayerHUDWidget.h"

#include "Components/STU_HealthComponent.h"

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
