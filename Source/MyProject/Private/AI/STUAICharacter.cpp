// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInit):Super(ObjectInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();
}