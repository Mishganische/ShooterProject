// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/STUMenuUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "STUGameInstance.h"

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
	
	if (!GetWorld()) return;
	
	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance) return;
	
	if (STUGameInstance->GetStartupLevelName().IsNone()) return;

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevelName());
}
