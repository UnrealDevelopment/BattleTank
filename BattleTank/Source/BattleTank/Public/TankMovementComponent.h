// Copyright reserved by Serhii D. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declarations
class UTankTrack;
/**
 * Responsible for fly-by-wire tank controls and AI pathfinding
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	UFUNCTION(BlueprintCallable, category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, category = Input)
	void IntendTurn(float Throw);

private:
	// Called in pathfinding UE logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
};
