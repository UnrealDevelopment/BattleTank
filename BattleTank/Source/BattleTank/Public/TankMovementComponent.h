// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// Forward Declarations
class UTankTrack;
/**
 * 
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
	UTankTrack* RightTrack = nullptr;
	UTankTrack* LeftTrack = nullptr;
};
