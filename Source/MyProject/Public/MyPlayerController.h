// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	
	virtual void OnPossess(APawn* InPawn) override;
};
