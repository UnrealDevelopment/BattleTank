// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	// Actual elevation speed
	auto ElevationSpeed = RelativeSpeed * MaxDegreesPerSecond;

	// Result barrel rotation for each frame
	auto RawFrameRotatation = RelativeRotation.Pitch + ElevationSpeed * GetWorld()->GetDeltaSeconds();

	// Clamp elevation angle in relate to possible position
	RawFrameRotatation = FMath::Clamp<float>(RawFrameRotatation, MinDegreesElevation, MaxDegreesElevation);
	
	SetRelativeRotation(FRotator(RawFrameRotatation, .0, .0));
}