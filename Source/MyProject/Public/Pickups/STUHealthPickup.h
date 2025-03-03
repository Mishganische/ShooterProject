// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASTUHealthPickup : public ASTUBasePickup
{
	GENERATED_BODY()

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
	
};
