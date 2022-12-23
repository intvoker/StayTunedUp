// Stay Tuned Up Game


#include "UI/STU_MenuButtonWidget.h"

#include "Components/Button.h"
#include "STU_GameInstance.h"

void USTU_MenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &ThisClass::OnMenuButton);
	}
}

void USTU_MenuButtonWidget::OnMenuButton()
{
	if (const auto STU_GameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>())
	{
		STU_GameInstance->StartLevel(STU_GameInstance->GetMenuLevelName());
	}
}
