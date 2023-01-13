// Stay Tuned Up Game


#include "Player/STU_PlayerController.h"

#include "Components/STU_RespawnComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/SpectatorPawn.h"
#include "STU_GameModeBase.h"

ASTU_PlayerController::ASTU_PlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTU_RespawnComponent>("RespawnComponent");
}

void ASTU_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bRotateSpectator)
		return;

	const auto OwnedPawn = GetPawnOrSpectator();
	if (!OwnedPawn)
		return;

	const float RotationAngle = RotationSpeed * DeltaSeconds;

	const FVector OwnedPawnLocation = OwnedPawn->GetActorLocation();
	const FVector FromRotationPoint = OwnedPawnLocation - RotationPoint;
	const FVector ToRotationPoint = -FromRotationPoint;

	const FVector NewLocation = RotationPoint + FromRotationPoint.RotateAngleAxis(RotationAngle, RotationAxis);
	const FRotator NewRotation = FRotationMatrix::MakeFromX(ToRotationPoint).Rotator();

	OwnedPawn->SetActorLocation(NewLocation);
	SetControlRotation(NewRotation);
}

void ASTU_PlayerController::GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	GetPlayerViewPoint(OutLocation, OutRotation);
}

FName ASTU_PlayerController::GetStartTag() const
{
	return !bOnlySpectator ? PlayerStartTag : SpectatorStartTag;
}

bool ASTU_PlayerController::IsStartTag(const FName& StartTag) const
{
	return StartTag.IsEqual(PlayerStartTag) || StartTag.IsEqual(SpectatorStartTag);
}

void ASTU_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerState)
	{
		PlayerState->SetIsOnlyASpectator(bOnlySpectator);
	}

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
