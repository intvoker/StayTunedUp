// Stay Tuned Up Game


#include "UI/STU_MenuHUD.h"

#include "Blueprint/UserWidget.h"

void ASTU_MenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass))
	{
		MenuWidget->AddToViewport();
	}
}
