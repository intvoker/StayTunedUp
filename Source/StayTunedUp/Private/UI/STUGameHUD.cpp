// Stay Tuned Up Game


#include "UI/STUGameHUD.h"

#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
}

void ASTUGameHUD::DrawCrosshair()
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
