// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/STUWeaponFXComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShotTimerHandle,this, &ASTURifleWeapon::MakeShot, TimeBetweenFire, true);
	MakeShot();
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void ASTURifleWeapon::MakeShot()
{
	if(!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}
	
	FVector TraceStart,TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}
	FHitResult HitResult;
	MakeHit(HitResult,TraceStart,TraceEnd);
	
	if(HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		//DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(),  HitResult.ImpactPoint,FColor::Red, false, 3.0f,0,3.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 7.0f, 32, FColor::Red,false,5.0f);
		WeaponFXComponent->PlayImpactFX(HitResult);

		//UE_LOG(LogBaseWeapon, Display, TEXT("Bone:%s"), *HitResult.BoneName.ToString());

	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(),  TraceEnd,FColor::Red, false, 3.0f,0,3.0f);
	}
	DecreaseAmmo();
}


bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
	
	TraceStart = ViewLocation; // SocketTransform.GetLocation();
	const auto HalfRad=FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection =FMath::VRandCone(ViewRotation.Vector(), HalfRad); // SocketTransform.GetRotation().GetForwardVector();
	TraceEnd =  TraceStart+ShootDirection*TraceMaxDistance;
	return true;
}


void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();
	if(!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}