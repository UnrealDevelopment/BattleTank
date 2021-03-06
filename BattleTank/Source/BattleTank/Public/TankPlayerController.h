// Copyright reserved by Serhii D. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward declarations
class UTankAimingComponent;

/**
 *  Responsible for helping the player to controll aiming process
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

protected:

	UFUNCTION(BlueprintImplementableEvent, category = Setup)
	void FoundAimingComponet(UTankAimingComponent* AimingComponent);
private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	int32 LineTraceRange = 10000;

	UTankAimingComponent* TankAimingComponent = nullptr;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	void AimTowardsCrosshair();
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UFUNCTION()
	void OnTankDeath();
};
