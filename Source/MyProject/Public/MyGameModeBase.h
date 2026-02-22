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
	
};
