// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STU_Types.h"
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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GamePausedWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameFinishedWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UUserWidget* CurrentGameWidget = nullptr;

	UPROPERTY()
	TMap<ESTU_GameMatchState, UUserWidget*> GameWidgets;

	UFUNCTION()
	void OnGameMatchStateChanged(ESTU_GameMatchState GameMatchState);

	void DrawCrosshair();
};
