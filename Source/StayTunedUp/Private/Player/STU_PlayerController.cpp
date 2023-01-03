// Stay Tuned Up Game


#include "Player/STU_PlayerController.h"

#include "Components/STU_RespawnComponent.h"
#include "GameFramework/SpectatorPawn.h"
#include "STU_GameModeBase.h"

ASTU_PlayerController::ASTU_PlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");
}

void ASTU_PlayerController::GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	GetPlayerViewPoint(OutLocation, OutRotation);
}

void ASTU_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		STU_GameModeBase->OnGameMatchStateChanged.AddDynamic(this, &ThisClass::HandleOnGameMatchStateChanged);
	}
}

void ASTU_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &ThisClass::PausePressed).bExecuteWhenPaused = true;
}

void ASTU_PlayerController::SetSpectatorPawn(ASpectatorPawn* NewSpectatorPawn)
{
	Super::SetSpectatorPawn(NewSpectatorPawn);

	if (NewSpectatorPawn)
	{
		NewSpectatorPawn->bUseControllerRotationPitch = true;
		NewSpectatorPawn->bUseControllerRotationYaw = true;
	}
}

void ASTU_PlayerController::PausePressed()
{
	if (const auto STU_GameModeBase = GetWorld()->GetAuthGameMode<ASTU_GameModeBase>())
	{
		if (!IsPaused())
		{
			STU_GameModeBase->SetPause(this);
		}
		else
		{
			STU_GameModeBase->ClearPause();
		}
	}
}

void ASTU_PlayerController::HandleOnGameMatchStateChanged(ESTU_GameMatchState GameMatchState)
{
	if (GameMatchState == ESTU_GameMatchState::Started)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}
