// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ChangeWeaponService.h"
#include "Components/STUWeaponComponent.h"
#include "AIController.h"
#include "STUUtils.h"

UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "Change Weapon";
}


void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && FMath::FRand()<=Probability && Probability>0)
		{
			WeaponComponent->NextWeapon();
		}
	}

	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
