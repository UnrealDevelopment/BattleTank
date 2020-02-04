// Copyright reserved by Serhii D. 
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

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
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		AimingStatus = EAimingStatus::Reloading;
	}
	else if(bIsBarrelMoving())
	{
		AimingStatus = EAimingStatus::Aiming;
	}
	else
	{
		AimingStatus = EAimingStatus::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret)
{
	if (!ensure(Barrel && Turret)){ return;	}
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//MoveTurretTowards(AimDirection);
	}
}
void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBP && Barrel)) { return; }
	if (AimingStatus != EAimingStatus::Reloading)
	{
		FVector NewLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
		FRotator NewRotator = Barrel->GetSocketRotation(FName("FiringPoint"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, NewLocation, NewRotator);
		Projectile->LaunchProjectile(LaunchSpeed);	
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	if (!ensure(Barrel && Turret)) { return; }
	//Current barrel rotation
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//Aim rotation
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the sortest path
	if (DeltaRotator.Yaw > 180 || DeltaRotator.Yaw < -180)
	{
		Turret->Turn(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Turn(DeltaRotator.Yaw);
	}
	
}

bool UTankAimingComponent::bIsBarrelMoving()
{
	if (!ensure(Barrel)){ return false; }
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.1);
}
