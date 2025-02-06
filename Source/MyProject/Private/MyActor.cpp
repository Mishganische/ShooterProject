// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogABOBAActor, All,All)

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	PrintTypes();
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::PrintTypes()
{
	FString Name = "John";
	UE_LOG(LogABOBAActor, Warning, TEXT("Name: %s"), *Name);
}

