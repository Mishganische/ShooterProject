// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestCharacter.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;

 
 
UCLASS()
class MYPROJECT_API ASTUAICharacter : public ATestCharacter
{
	GENERATED_BODY()

public:
	ASTUAICharacter(const FObjectInitializer& ObjectInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

protected:
	virtual void OnDeath() override;
};
