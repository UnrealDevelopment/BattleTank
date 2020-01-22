// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // TODO deside if it really has to tick

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto ThisTankName = GetOwner()->GetName();

	// Components initialization check
	if (!Barrel && !Turret)
	{
		return;
	}

	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
	FVector OutLaunchVelocity(0);

	bool bValidSolution = false;
	bValidSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		.0,
		.0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bValidSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurret(UTankTurret* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	//Current barrel rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//Aim rotation
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	// Current turret rotation
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	// Aim rotation
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Turn(DeltaRotator.Yaw);
}
