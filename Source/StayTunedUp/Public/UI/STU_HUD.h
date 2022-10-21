// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STU_HUD.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API ASTU_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawCrosshair();
};
