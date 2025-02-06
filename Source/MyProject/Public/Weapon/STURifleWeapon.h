// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

UCLASS()
class MYPROJECT_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeBetweenFire = 0.2f;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BulletSpread = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageAmount = 10.0f;
    	


	
private:
	FTimerHandle ShotTimerHandle;
	void MakeDamage(const FHitResult& HitResult);
};
