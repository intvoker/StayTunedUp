// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GamePausedWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GamePausedWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* ClearPauseButton;

private:
	UFUNCTION()
	void OnClearPauseButton();
};
