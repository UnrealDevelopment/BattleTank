// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)){ return; }
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)){ return; }
	if (!PlayerTank){ return; } // If Player's is destroyed stopaiming  
	
	//DrawDebugSphere(GetWorld(), GetPawn()->GetActorLocation(), 5000.f, 32, FColor::Red);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetPawn()->GetActorLocation().ToCompactString())
	
	// MoveToActor ignores acceptance rate while MoveToLocation works just fine
	// MoveToActor(Cast<AActor>(PlayerTank), 5000.f);
	MoveToLocation(PlayerTank->GetActorLocation(), AcceptanceRate);

	TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (TankAimingComponent->GetAimingStatus() == EAimingStatus::Locked)
	{
		TankAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		// Bind delegate
		PossessedTank->OnDeathEvent.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
	//UE_LOG(LogTemp, Warning, TEXT("On AI tank death debug print"))
}
