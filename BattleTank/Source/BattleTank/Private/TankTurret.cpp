// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	// Actual rotation speed
	auto RotationSpeed = RelativeSpeed * MaxDegreesPerSecond;

	// Rotation for each frame
	auto RawFrameRotation = RelativeRotation.Yaw + RotationSpeed * GetWorld()->GetDeltaSeconds();
	
	SetRelativeRotation(FRotator(.0, RawFrameRotation, .0));

}