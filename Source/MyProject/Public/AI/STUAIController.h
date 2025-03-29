// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;


UCLASS()
class MYPROJECT_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASTUAIController();
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Components")
	USTUAIPerceptionComponent* STUAIPerceptionComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;


private:
	AActor* GetFocusOnACtor() const;
	
	
};
