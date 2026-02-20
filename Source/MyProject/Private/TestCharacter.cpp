// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"

#include "Components/STUWeaponComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/InputComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
//#include "GameFramework/DamageType.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "STUCharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "STUHealthComponent.h"
//#include "STUHealthComponentPro.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog,All,All);


// Sets default values
ATestCharacter::ATestCharacter(const FObjectInitializer& ObjInit):Super (ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation=true;
	SpringArmComponent->SocketOffset=FVector(0.0f,100.0f,80.0f);

	
	CameraComponent= CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	
	STUHealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");


	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(GetRootComponent());
	TextRenderComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(STUHealthComponent);
	check(TextRenderComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(STUHealthComponent->GetHealth(), 0.0f);
	STUHealthComponent->OnDeath.AddUObject(this, &ATestCharacter::OnDeath);
	STUHealthComponent->OnHealthChanged.AddUObject(this, &ATestCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this,&ATestCharacter::OnGroundLanded);
	
}


// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TakeDamage(0.1f, FDamageEvent {}, Controller, this);
}



// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	check(WeaponComponent)
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ATestCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ATestCharacter::TurnRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATestCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATestCharacter::OnFastRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ATestCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USTUWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFire);
	PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Released, WeaponComponent, &USTUWeaponComponent::PreviousWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Released, WeaponComponent, &USTUWeaponComponent::Reload);
}

void ATestCharacter::MoveForward(float Value)
{
	IsMoving = Value> 0.0f;
	if (Value==0.0f) return;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ATestCharacter::MoveRight(float Value)
{
	if (Value==0.0f) return;
	AddMovementInput(GetActorRightVector(),Value);
}

void ATestCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ATestCharacter::TurnRight(float Value)
{
	AddControllerYawInput(Value);
}


void ATestCharacter::OnFastRunning()
{
	WantsToRun=true;
}

void ATestCharacter::OnStopRunning()
{
	WantsToRun=false;
}


bool ATestCharacter::IsRunning() const
{
	return WantsToRun && IsMoving && !GetVelocity().IsZero();
}

float ATestCharacter::GetActorDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(VelocityNormal,GetActorForwardVector()));
	const auto CrossProduct = FVector::CrossProduct(VelocityNormal,GetActorForwardVector());
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees* FMath::Sign(CrossProduct.Z);
}


void ATestCharacter::OnDeath()
{
	UE_LOG(BaseCharacterLog, Display, TEXT("Player %s is dead!"), *GetName());

	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(10.0f);

	Controller->ChangeState(NAME_Spectating);

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WeaponComponent->StopFire();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ATestCharacter::OnHealthChanged(float Health, float HealthDelta)
{
	TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ATestCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	if (FallVelocityZ < VelocityLandedDamage.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(VelocityLandedDamage, LandedDamage, FallVelocityZ);

	FDamageEvent DamageEvent;
	TakeDamage(FinalDamage, DamageEvent, nullptr, nullptr);
	
}








