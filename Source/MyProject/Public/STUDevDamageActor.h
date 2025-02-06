// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class MYPROJECT_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Damage")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Radius=300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	bool DoFullDamage=false;

	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category="Damage")
	TSubclassOf<UDamageType> DamageType;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
