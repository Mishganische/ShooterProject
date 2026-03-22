// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/STUMenuGameModeBase.h"
#include "Menu/UI/STUMenuHUD.h"
#include "Menu/STUMenuPlayerController.h"

ASTUMenuGameModeBase::ASTUMenuGameModeBase()
{
	PlayerControllerClass = ASTUMenuPlayerController::StaticClass();
	HUDClass = ASTUMenuHUD::StaticClass();
}
