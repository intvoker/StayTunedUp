// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_MenuButtonWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_MenuButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* MenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void HandleOnClickedMenu();
};
