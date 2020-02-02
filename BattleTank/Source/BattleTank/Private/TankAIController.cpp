// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(ControlledTank && PlayerTank)){ return; }
	MoveToActor(PlayerTank, AcceptanceRate); 
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	//ControlledTank->Fire(); TODO uncommit to allow AI tanks firing
}
