// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "TestCharacter.h"
#include "AI/STUAIController.h"
#include "UI/STUHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyGameModeBase, All, All);

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ATestCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	SpawnBots();
	
	CurrentRound = 1;
	StartRound();
}

UClass* AMyGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<ASTUAIController>())
	{
		return AIPawnClass;
	}
	
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}


void AMyGameModeBase::SpawnBots()
{
	if (!GetWorld()) return;

	for (int i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const auto STUCOntroller = GetWorld()->SpawnActor<ASTUAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(STUCOntroller);
		
	}
}

void AMyGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(TimerRoundHandle, this, &AMyGameModeBase::GameTimerUpdate,1.0f, true);
}

void AMyGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogMyGameModeBase, Log, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerRoundHandle);
		if (CurrentRound + 1 <= GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogMyGameModeBase, Warning, TEXT("GAME OVER"));
		}
	}
}

void AMyGameModeBase::ResetPlayers()
{
	if (!GetWorld()) return;
	
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		ResetOnePlayer(It->Get());
	}
}

void AMyGameModeBase::ResetOnePlayer(AController* Controller)
{
	if (Controller || Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
		RestartPlayer(Controller);
	}
}
