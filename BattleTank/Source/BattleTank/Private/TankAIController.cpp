// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ControlledTank || !PlayerTank)
	{
		return;
	}
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire(); // Add fire rate
}
