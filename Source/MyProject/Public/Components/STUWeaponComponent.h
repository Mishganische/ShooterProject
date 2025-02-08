// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
	UPROPERTY(EditDefaultsOnly, category = "Weapon")
	TArray <TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, category = "Weapon")
	FName WeaponEquipSocketName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;
	

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray <ASTUBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex =0;
	
	void SpawnWeapons();
	void AttachWeaponToSocket( ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon (int32 WeaponIndex);
	void PlayAnimMontage(UAnimMontage* Animation);
};
