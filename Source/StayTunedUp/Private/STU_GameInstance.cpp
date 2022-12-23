// Stay Tuned Up Game


#include "STU_GameInstance.h"

#include "Kismet/GameplayStatics.h"

void USTU_GameInstance::StartLevel(FName LevelName) const
{
	if (LevelName.IsNone())
		return;

	UGameplayStatics::OpenLevel(this, LevelName);
}

void USTU_GameInstance::RestartCurrentLevel() const
{
	StartLevel(FName(UGameplayStatics::GetCurrentLevelName(this)));
}

void USTU_GameInstance::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
