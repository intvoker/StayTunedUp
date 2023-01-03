// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_MenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void HandleOnClickedStartGame();

	UFUNCTION()
	void HandleOnClickedExitGame();
};
