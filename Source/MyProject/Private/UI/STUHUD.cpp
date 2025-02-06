// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUHUD.h"
#include "Engine/Canvas.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrosshair();
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