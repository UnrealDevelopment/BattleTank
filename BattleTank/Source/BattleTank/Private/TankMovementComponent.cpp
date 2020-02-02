// Copyright reserved by Serhii D. 

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!ensure(LeftTrack && RightTrack)) { return; } // Pointer protection
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; } // Pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; } // Pointer protection
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

// Overriding engine method to perfom AI tank movement using tank movement component
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float DotProduct = FVector::DotProduct(TankForward, AIForwardIntention); // Throw to apply movement
	float CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntention).Z; // Throw to apply turning

	IntendTurn(CrossProduct);
	IntendMoveForward(DotProduct);
}
