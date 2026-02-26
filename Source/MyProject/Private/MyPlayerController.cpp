// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Components/STURespawnComponent.h"

AMyPlayerController::AMyPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}
