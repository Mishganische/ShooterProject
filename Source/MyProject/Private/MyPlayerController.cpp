// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "MyGameModeBase.h"
#include "STUGameInstance.h"

AMyPlayerController::AMyPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AMyPlayerController::OnMatchStateChanged);
		}
	}
}

void AMyPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void AMyPlayerController::OnMuteSound()
{
	if (!GetWorld()) return;
	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;
	
	STUGameInstance->ToggleVolume();
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	OnNewPawn.Broadcast(InPawn);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;
	
	InputComponent->BindAction("GamePause", IE_Pressed, this, &AMyPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &AMyPlayerController::OnMuteSound);
}

void AMyPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	
	GetWorld() ->GetAuthGameMode()->SetPause(this);
}




