// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"
#include "Engine/World.h"
#include "..\Public\Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrel(UTankBarrel* Barrel)
{
	TankAimingComponent->SetBarrel(Barrel);
	this->Barrel = Barrel;
}

void ATank::SetTurret(UTankTurret* Turret)
{
	TankAimingComponent->SetTurret(Turret);
}

void ATank::Fire()
{
	if (!ProjectileBP)
	{
		return;
	}
	FVector NewLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
	FRotator NewRotator = Barrel->GetSocketRotation(FName("FiringPoint"));

	GetWorld()->SpawnActor<AProjectile>(ProjectileBP, NewLocation, NewRotator);

	UE_LOG(LogTemp, Warning, TEXT("Fire!"))
}

