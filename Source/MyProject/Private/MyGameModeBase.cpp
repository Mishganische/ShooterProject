// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "TestCharacter.h"
#include "UI/STUHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = ATestCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
}
