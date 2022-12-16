// Stay Tuned Up Game


#include "UI/STU_HUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"
#include "STU_GameModeBase.h"

void ASTU_HUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrosshair();
}

void ASTU_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
	{
		PlayerHUDWidget->AddToViewport();
	}

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->OnGameMatchStateChanged.AddDynamic(this, &ThisClass::OnGameMatchStateChanged);
	}
}

void ASTU_HUD::OnGameMatchStateChanged(ESTU_GameMatchState GameMatchState)
{
	UE_LOG(LogTemp, Warning, TEXT("GameMatchState: %s."), *UEnum::GetValueAsString(GameMatchState));
}

void ASTU_HUD::DrawCrosshair()
{
	const float LineHalfSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;

	//FVector2D Center(Canvas->SizeX / 0.5f, Canvas->SizeY / 0.5f);
	FVector2D Center;
	Canvas->GetCenter(Center.X, Center.Y);

	const TInterval<float> LineX(Center.X - LineHalfSize, Center.X + LineHalfSize);
	const TInterval<float> LineY(Center.Y - LineHalfSize, Center.Y + LineHalfSize);

	DrawLine(LineX.Min, Center.Y, LineX.Max, Center.Y, LineColor, LineThickness);
	DrawLine(Center.X, LineY.Min, Center.X, LineY.Max, LineColor, LineThickness);
}
