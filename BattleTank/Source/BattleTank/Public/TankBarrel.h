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
	void Elevate(float DegreesPerSecond);

private:
	//Sensinble defaults	
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MaxDegreesElevation = 50;
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MinDegreesElevation = 0;
	UPROPERTY(EditAnyWhere, Category = Setup)
	float MaxDegreesPerSecond = 20;	




};
