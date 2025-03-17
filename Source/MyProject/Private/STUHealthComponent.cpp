// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
//#include "Dev/STUFireDamageType.h"
//#include "Dev/STUIceDamageType.h"


//DEFINE_LOG_CATEGORY_STATIC(HealthProLogComponent, All, All)

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	check(MaxHealth > 0);

	SetHealth(MaxHealth);
	//OnHealthChanged.Broadcast(Health, HealthDelta);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
	

}


void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage<=0.0f || IsDead() || !GetWorld()) return;
	
	SetHealth(Health-Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (IsAutoHealth)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}

	PlayCameraShake();
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



void USTUHealthComponent::HealUpdate()
{
		SetHealth(Health + HealModifier);

	if (IsHealthFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}

void USTUHealthComponent::PlayCameraShake()
{
	if(IsDead()) return;
	const auto Player = Cast<APawn>(GetOwner());

	if(!Player)return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}


void USTUHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth=  FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta  = NextHealth - Health;
	
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health, HealthDelta);
}


bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
	if (IsDead() || IsHealthFull()) return false;
	SetHealth(Health+HealthAmount);
	return true;
}

bool USTUHealthComponent::IsHealthFull() const
{
	return FMath::IsNearlyEqual(Health,MaxHealth);
}







