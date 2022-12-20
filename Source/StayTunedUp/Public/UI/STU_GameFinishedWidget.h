// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GameFinishedWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GameFinishedWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* RestartLevelButton;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnRestartLevelButton();
};
