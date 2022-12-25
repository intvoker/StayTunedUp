// Stay Tuned Up Game


#include "STU_GameInstance.h"

#include "Kismet/GameplayStatics.h"

void USTU_GameInstance::StartLevel(FName LevelName) const
{
	if (LevelName.IsNone())
		return;

	UGameplayStatics::OpenLevel(GetWorld(), LevelName);
}

void USTU_GameInstance::RestartCurrentLevel() const
{
	StartLevel(FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

void USTU_GameInstance::ExitGame() const
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}
