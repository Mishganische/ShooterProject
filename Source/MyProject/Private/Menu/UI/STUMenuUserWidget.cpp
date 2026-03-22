// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void USTUMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuUserWidget::OnStartGame);
	}
}

void USTUMenuUserWidget::OnStartGame()
{
	const FName StartupLevelName("TestMap2");
	UGameplayStatics::OpenLevel(this, StartupLevelName);
}
