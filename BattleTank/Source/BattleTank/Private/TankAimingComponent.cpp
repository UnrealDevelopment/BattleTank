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
	PrimaryComponentTick.bCanEverTick = false; // TODO deside if it really has to tick
	//UE_LOG(LogTemp, Warning, TEXT("SEQUENCE LOG: TankAimingComponent.cpp->Constructor()"))
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* Barrel, UTankTurret* Turret)
{
	if (!ensure(Barrel && Turret))
	{
		UE_LOG(LogTemp, Warning, TEXT("No turret or barrel initialized"))
		return;
	}
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
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
void UTankAimingComponent::Fire()
{
	if (!ensure(ProjectileBP)) { return; }
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (bIsReloaded)
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
