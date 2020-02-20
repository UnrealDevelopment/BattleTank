// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track holds track properties such as maximum driving force and allows to apply forces to a tank
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	virtual void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);
	
private:
	// Maximum force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 60000000;

	TArray<class ASprungWheel*> GetWheels() const;
};
