// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class USTURespawnComponent;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	USTURespawnComponent* RespawnComponent;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	
private:
	void OnPauseGame();
	void OnMatchStateChanged(ESTUMatchState State);
};
