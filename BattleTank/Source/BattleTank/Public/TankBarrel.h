// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel's properties
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed); // -1 is min amd +1 is max speed

private:
	//Sensinble defaults	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesElevation = 40;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegreesElevation = 0;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10;	
};
