// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickup.h"
#include "STUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASTUAmmoPickup : public ASTUBasePickup
{
	GENERATED_BODY()


private:
	virtual bool GivePickupTo(APawn* PlayerPawn);
};
