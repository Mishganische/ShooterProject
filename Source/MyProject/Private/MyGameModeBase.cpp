// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "STUUtils.h"
#include "TestCharacter.h"
#include "AI/STUAIController.h"
#include "Components/STURespawnComponent.h"
#include "UI/STUHUD.h"
#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogMyGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ATestCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
	PlayerStateClass = ASTUPlayerState::StaticClass();
}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	SpawnBots();
	CreateTeamsInfo();
	
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

void AMyGameModeBase::Killed(AController* KillerController, AController* VictimController)
{

	const auto KillerPlayerState = KillerController ? Cast<ASTUPlayerState>(KillerController->PlayerState) : nullptr;
	const auto VictimPlayerState = VictimController ? Cast<ASTUPlayerState>(VictimController->PlayerState) : nullptr;
	
	if ( KillerPlayerState)
	{
		KillerPlayerState->AddKill();
	}
	
	if (VictimPlayerState)
	{
		VictimPlayerState->AddDeath();
	}
	
	StartRespawn(VictimController);
}

void AMyGameModeBase::RequestRespawn(AController* Controller)
{
	ResetOnePlayer(Controller);
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
			LogPlayerInfo();
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
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
	SetPlayerColor(Controller);
}

void AMyGameModeBase::CreateTeamsInfo()
{
	if (!GetWorld()) return;
	
	int32 TeamID = 1;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) return;
		
		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) return;
		
		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
		SetPlayerColor(Controller);
		
		TeamID = TeamID == 1 ? 2 : 1;
	}
	
}

FLinearColor AMyGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
	if (TeamID-1 < GameData.TeamColors.Num())
	{
		return GameData.TeamColors[TeamID-1];
	}
	
	return GameData.DefaultTeamColor;
}

void AMyGameModeBase::SetPlayerColor(AController* Controller)
{
	if (!Controller) return;
	
	const auto Character = Cast<ATestCharacter>(Controller->GetPawn());
	if (!Character) return;
	
	const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
	if (!PlayerState) return;
	
	Character->SetPlayerColor(PlayerState->GetTeamColor());
	
}

void AMyGameModeBase::LogPlayerInfo()
{
	if (!GetWorld()) return;
	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) return;
		
		const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) return;
		
		PlayerState->LogInfo();
	}
}

void AMyGameModeBase::StartRespawn(AController* Controller)
{
	const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
	if (!RespawnAvailable) return;
	const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(Controller);
	if (!RespawnComponent) return;
	
	RespawnComponent->Respawn(GameData.RespawnTime);
}
