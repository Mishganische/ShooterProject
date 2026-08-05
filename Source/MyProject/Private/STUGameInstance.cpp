// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameInstance.h"
#include "Sound/STUSoundFuncLibrary.h"

void USTUGameInstance::ToggleVolume()
{
	USTUSoundFuncLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
