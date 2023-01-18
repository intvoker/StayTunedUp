// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STU_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STAYTUNEDUP_API USTU_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void StartLevel(FName LevelName) const;
	void RestartCurrentLevel() const;

	void ExitGame() const;

	FName GetMenuLevelName() const { return FName(MenuLevel.GetAssetName()); }
	FName GetDiskLevelName() const { return FName(DiskLevel.GetAssetName()); }
	FName GetTestLevelName() const { return FName(TestLevel.GetAssetName()); }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game", meta=(AllowedClasses="World"))
	FSoftObjectPath MenuLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta=(AllowedClasses="World"))
	FSoftObjectPath DiskLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Game", meta=(AllowedClasses="World"))
	FSoftObjectPath TestLevel;
};
