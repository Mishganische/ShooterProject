// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature);

class USkeletalMeshComponent;


UCLASS()
class MYPROJECT_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUBaseWeapon();

	FOnClipEmptySignature OnClipEmpty;

	void ChangeClip();
	bool CanReload() const;
	
	virtual void StartFire();
	virtual void StopFire();


	FWeaponUIData GetUIData() const {return UIData;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoData DefaultAmmo{15,30,false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "UI")
	FWeaponUIData UIData;



	virtual void MakeShot();

	APlayerController* GetPlayerController()const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);


	void DecreaseAmmo();
	bool IsAmmoEmpty() const;
	bool IsClipsEmpty() const;
private:
	FAmmoData CurrentAmmo;
};
