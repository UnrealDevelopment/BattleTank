// Copyright reserved by Serhii D. 

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h" 
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(TankAimingComponent))
	{
		FoundAimingComponet(TankAimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming component is not found by the time Player Controller begins to play"))
	}
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeathEvent.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}

}
void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
	//UE_LOG(LogTemp, Warning, TEXT("On Player tank death debug print"))
}
void ATankPlayerController::AimTowardsCrosshair()
{	
	if (!GetPawn()){ return; }// if not possess
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }
	FVector HitLocation;
	GetSightRayHitLocation(HitLocation); 
	TankAimingComponent->AimAt(HitLocation);
}

// Deproject aim pointer on screen to world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

// Find world location based on look direction and line trace range
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (!GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Camera))
	{
		OutHitLocation = FVector(0);
		return false;
	}
	OutHitLocation = HitResult.Location;
	return true;
}

// Get locatin that screen aim points to
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewPortSizeX;
	int32 ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	//DrawDebugLine(GetWorld(), GetPawn()->GetActorLocation(), WorldDirection*1000000, FColor(255, 0, 255), false, -1, 0, 12.333);
	return false;
}
