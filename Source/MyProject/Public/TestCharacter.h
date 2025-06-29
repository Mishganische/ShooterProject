// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;

UCLASS()
class MYPROJECT_API ATestCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestCharacter(const FObjectInitializer& ObjInit);
	

protected:
	// Called when the game starts or when spawned

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	USpringArmComponent* SpringArmComponent;


	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, category = "Components")
	USTUHealthComponent* STUHealthComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, category = "Components")
	USTUWeaponComponent* WeaponComponent;
	
	UPROPERTY(EditDefaultsOnly, category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, category = "Damage")
	FVector2D VelocityLandedDamage = FVector2D(900.0f, 1200.0f);

	UPROPERTY(EditDefaultsOnly, category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);
	

	
	
	virtual void BeginPlay() override;
	virtual void OnDeath();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetActorDirection() const;

	

private:
	//Running
	bool WantsToRun = false;
	bool IsMoving = false;

	//Moving
	void MoveForward(float Value);
	void MoveRight(float Value);
	void OnFastRunning();
	void OnStopRunning();

	//camera moving
	void LookUp(float Value);
	void TurnRight(float Value);

	//Death and Damaging
	void OnHealthChanged(float Health, float HealthDelta);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	
};
