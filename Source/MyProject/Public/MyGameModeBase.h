// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "MyGameModeBase.generated.h"

class ASTUAIController;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();
	virtual void StartPlay();
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
	
	void Killed(AController* KillerController, AController* VictimController);
	
	FGameData GetGameData() const {return GameData;}
	int32 GetCurrentRound() const {return CurrentRound;}
	int32 GetRoundSecondsRemaining() const {return RoundCountDown;}
	void RequestRespawn(AController* Controller);
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf <ASTUAIController> AIControllerClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf <APawn> AIPawnClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;
	
private:
	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();
	
	
	int32 CurrentRound {1};
	int32 RoundCountDown {0};
	FTimerHandle TimerRoundHandle;
	
	
	void ResetPlayers();
	void ResetOnePlayer(AController* Controller);
	
	void CreateTeamsInfo();
	FLinearColor DetermineColorByTeamID(int32 TeamID) const;
	void SetPlayerColor(AController* Controller);
	
	void LogPlayerInfo();
	
	void StartRespawn(AController* Controller);
	
};
