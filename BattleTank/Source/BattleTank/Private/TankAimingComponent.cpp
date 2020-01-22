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
	PrimaryComponentTick.bCanEverTick = true; // TODO deside if it really has to tick

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto ThisTankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s aims from %s"), *ThisTankName, Barrel->Get);

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
	

	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: %s has a suggested launch velocity of %s, is valid = %d"), Time, *ThisTankName, *AimDirection.ToString(), bValidSolution)
}

void UTankAimingComponent::SetBarrel(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurret(UTankTurret* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("Barrel Rotation is %s. Aim as rotator = %s. Delta rotator = %s"), *BarrelRotator.ToString(), *AimAsRotator.ToString(), *DeltaRotator.ToString())

	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
    //UE_LOG(LogTemp, Warning, TEXT("Turret Rotation is %s. Aim as rotator = %s. Delta rotator = %s"), *TurretRotator.ToString(), *AimAsRotator.ToString(), *DeltaRotator.ToString())
	UE_LOG(LogTemp, Warning, TEXT("Aim Yaw rotation is %f, delta rotation is %f, turret rotation is %f"), AimAsRotator.Yaw, DeltaRotator.Yaw, TurretRotator.Yaw)

	Turret->Turn(DeltaRotator.Yaw);
	
	
}
