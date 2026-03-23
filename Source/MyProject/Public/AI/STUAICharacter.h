// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

 
 
UCLASS()
class MYPROJECT_API ASTUAICharacter : public ATestCharacter
{
	GENERATED_BODY()

public:
	
	ASTUAICharacter(const FObjectInitializer& ObjectInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* HealthWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	float HealthVisibilityDistance = 1000.0f;
	
	virtual void BeginPlay() override;
	
	virtual void OnDeath() override;
	
	virtual void OnHealthChanged(float Health, float HealthDelta) override;


private:
	void UpdateHealthWidgetVisibility();
};
