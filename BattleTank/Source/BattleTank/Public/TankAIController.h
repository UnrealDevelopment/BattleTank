// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

private:
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(EditAnywhere, category = Setup)
	float AcceptanceRate = 10000.0f;

	UFUNCTION()
	void OnTankDeath();
};
