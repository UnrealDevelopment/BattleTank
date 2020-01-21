// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

	if (!Barrel)
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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	

	FVector AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrelTowards(AimDirection);
	//UE_LOG(LogTemp, Warning, TEXT("%s has a suggested launch velocity of %s, is valid = %d"), *ThisTankName, *AimDirection.ToString(), bValidSolution)
}

void UTankAimingComponent::SetBarrel(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("Aim as rotator = %s. Delta rotator = %s"), *AimAsRotator.ToString(), *DeltaRotator.ToString())

	Barrel->Elevate(5);

}