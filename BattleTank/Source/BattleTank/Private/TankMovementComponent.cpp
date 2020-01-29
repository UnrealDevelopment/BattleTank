// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

// TODO Prevent speed doubeling due to dual control usage 
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack && !RightTrack) { return; } // Pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!LeftTrack && !RightTrack) { return; } // Pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	//UE_LOG(LogTemp, Warning, TEXT("Intend to move forward. Throw is %f"), Throw)
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float DotProduct = FVector::DotProduct(TankForward, AIForwardIntention); // Throw to apply movement

	float CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntention).Z; // Throw to apply turning

	

	IntendTurn(CrossProduct);
	IntendMoveForward(DotProduct);

	/*
	float Time = GetWorld()->GetTimeSeconds();
	auto Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Tank %s has requested move velocity %s"), *Name, *MoveVelocity.ToString())
	UE_LOG(LogTemp, Warning, TEXT("%f: Dot product is  %f. Call from RequestDirectMove"), Time, DotProduct)
	*/
}
