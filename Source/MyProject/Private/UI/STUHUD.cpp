// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUHUD.h"
#include "Engine/Canvas.h"
#include "UI/STUHUD.h"

#include "MyGameModeBase.h"
#include "Blueprint/UserWidget.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrosshair();
}

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();
	
	GameWidgets.Add(ESTUMatchState::InProgress,CreateWidget<UUserWidget> (GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause,CreateWidget<UUserWidget> (GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver,CreateWidget<UUserWidget> (GetWorld(), GameOverWidgetClass));
	
	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GetWorld())
	{
		const auto GameMode = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUHUD::OnMatchStateChanged);
		}
	}
}


void ASTUHUD::DrawCrosshair()
{
	int32 SizeX = Canvas->SizeX;
	int32 SizeY = Canvas->SizeY;

	const TInterval<float> Center (SizeX*0.5f,SizeY*0.5f );

	const float HalfLineSize = 10.0f;
	const float Thickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Green;

	DrawLine(Center.Min-HalfLineSize, Center.Max, Center.Min+HalfLineSize, Center.Max, LinearColor, Thickness);
	DrawLine(Center.Min,Center.Max-HalfLineSize, Center.Min, Center.Max+HalfLineSize, LinearColor, Thickness);                       
}

void ASTUHUD::OnMatchStateChanged(ESTUMatchState State)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}
	
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
}
