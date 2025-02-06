// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacterMovementComponent.h"
#include "TestCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ATestCharacter* Player = Cast<ATestCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * SpeedModifier : MaxSpeed;
}
