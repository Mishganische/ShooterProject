// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STUFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USTUFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	USTUFindEnemyService();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
