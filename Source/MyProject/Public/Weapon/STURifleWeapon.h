// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
class UNiagaraComponent;
class  UNiagaraSystem;
class UAudioComponent;

UCLASS()
class MYPROJECT_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	ASTURifleWeapon();
	
	
	virtual void StartFire() override;
	virtual void StopFire() override;
	
	virtual void Zoom(bool Enabled) override;

protected:
	virtual void BeginPlay() override;
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float TimeBetweenFire = 0.2f;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float BulletSpread = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	UNiagaraSystem* TraceFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	FString TraceTargetName = "TraceTarget";

	UPROPERTY(VisibleAnywhere, category = "VFX")
	USTUWeaponFXComponent* WeaponFXComponent;
    	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float FOVZoomAngle = 50.0f;

	
private:
	FTimerHandle ShotTimerHandle;
	
	UPROPERTY()
	UNiagaraComponent* MuzzleFXComponent;
	
	UPROPERTY()
	UAudioComponent* FireAudioComponent;
	
	void MakeDamage(const FHitResult& HitResult);

	void InitFX();
	void SetFXActive(bool IsActive);
	void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);
	
	AController* GetController() const;
	
	float DefaultCameraFOV = 90.0f;
};
