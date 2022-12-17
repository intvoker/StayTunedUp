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

	GameWidgets.Add(ESTU_GameMatchState::Started, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTU_GameMatchState::Paused, CreateWidget<UUserWidget>(GetWorld(), GamePausedWidgetClass));

	for (const auto GameWidgetTuple : GameWidgets)
	{
		const auto GameWidget = GameWidgetTuple.Value;
		if (!GameWidget)
			continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->OnGameMatchStateChanged.AddDynamic(this, &ThisClass::OnGameMatchStateChanged);
	}
}

void ASTU_HUD::OnGameMatchStateChanged(ESTU_GameMatchState GameMatchState)
{
	if (CurrentGameWidget)
	{
		CurrentGameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameWidgets.Contains(GameMatchState))
	{
		CurrentGameWidget = GameWidgets[GameMatchState];
	}
	if (CurrentGameWidget)
	{
		CurrentGameWidget->SetVisibility(ESlateVisibility::Visible);
	}

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
