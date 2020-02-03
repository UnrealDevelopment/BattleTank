// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Side speed that happens due to slipping tracks
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	
	// Correction acceleration 
	auto Acceleration = SlippageSpeed / DeltaTime * (-GetRightVector());

	// Find correction force F = m*a
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->CalculateMass() * Acceleration) / 2;

	TankRoot->AddForce(CorrectionForce);

	

	//UE_LOG(LogTemp, Warning, TEXT("SlippageSpeed is %s"), *CorrectionForce.ToString())
}


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplyed = GetForwardVector() * Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplyed, ForceLocation);
}
