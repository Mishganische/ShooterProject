// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	float GetHealth() const {return Health;}

	UFUNCTION(BlueprintCallable, category = "Health")
	bool IsDead () const {return FMath::IsNearlyZero(Health);}

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent()const {return Health/MaxHealth;}

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull()const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AutoHealth")
	bool IsAutoHealth = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AutoHealth", meta=(EditCondition="IsAutoHealth"))
	float HealUpdateTime = 0.3f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AutoHealth", meta=(EditCondition="IsAutoHealth"))
	float HealDelay = 3.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AutoHealth", meta=(EditCondition="IsAutoHealth"))
	float HealModifier=1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;
	


private:
	FTimerHandle TimerHandle_HealDelay;
	FTimerHandle HealTimerHandle;
	float Health = 0.0f;
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	

	void SetHealth(float NewHealth);
	void HealUpdate();

	void PlayCameraShake();
	
	void Killed(AController* KillerController);
};
