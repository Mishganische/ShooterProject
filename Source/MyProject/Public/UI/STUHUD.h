// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUCoreTypes.h"
#include "STUHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASTUHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TMap<ESTUMatchState, UUserWidget*> GameWidgets;
	
	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
	
	
	
	void DrawCrosshair();
	void OnMatchStateChanged(ESTUMatchState State);
	
};
