// Fill out your copyright notice in the Description page of Project Settings.

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
	auto BarrelLocation = Barrel->GetSocketLocation(FName("Barrel"));
	UE_LOG(LogTemp, Warning, TEXT("%s aims at %s from %s"), *ThisTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* Barrel)
{
	this->Barrel = Barrel;
}
