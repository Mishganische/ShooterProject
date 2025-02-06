// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponentPro.h"
#include "GameFramework/Actor.h"
//#include "Dev/STUFireDamageType.h"
//#include "Dev/STUIceDamageType.h"


//DEFINE_LOG_CATEGORY_STATIC(HealthProLogComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponentPro::USTUHealthComponentPro()
{

	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void USTUHealthComponentPro::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponentPro::OnTakeAnyDamage);
	}
	

}

void USTUHealthComponentPro::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage<=0.0f || IsDead()) return;
	
	Health = FMath::Clamp(Health-Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	


	/*UE_LOG(HealthLogComponent, Display, TEXT("Damage: %f"), Damage);
	if (DamageType)
	{
		if (DamageType->IsA<USTUIceDamageType>())
		{
			UE_LOG(HealthLogComponent, Display, TEXT("So COOOOOOLLLLLD!!!!"));
		}
		else if (DamageType->IsA<UMyDamageType>())
		{
			UE_LOG(HealthLogComponent, Display, TEXT("VERY HOOOOOT!!!"));
		}
	}*/
}






