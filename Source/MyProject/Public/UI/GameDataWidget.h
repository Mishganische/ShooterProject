// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameDataWidget.generated.h"

class ASTUPlayerState;
class AMyGameModeBase;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundNum() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;
	
private:
	AMyGameModeBase* GetGameMode() const;
	ASTUPlayerState* GetPlayerState() const;
	
};
