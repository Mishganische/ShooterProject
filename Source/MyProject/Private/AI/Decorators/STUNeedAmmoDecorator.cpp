// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/STUNeedAmmoDecorator.h"
#include "STUUtils.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"

USTUNeedAmmoDecorator::USTUNeedAmmoDecorator()
{
	NodeName = "Health Percent";
}

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;

	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->NeedAmmo(WeaponType);
	
}


