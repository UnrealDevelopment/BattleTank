// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "WheelSpawnPoint.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//UE_LOG(LogTemp, Warning, TEXT("SlippageSpeed is %s"), *CorrectionForce.ToString())
}



void UTankTrack::SetThrottle(float Throttle)
{
	auto CurrentThrottle = FMath::Clamp<float>(Throttle, -1, +1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplyed = CurrentThrottle * MaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplyed / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> OutTrackChildren;
	GetChildrenComponents(false, OutTrackChildren);
	TArray<ASprungWheel*> Result;
	for (USceneComponent* Child : OutTrackChildren)
	{
		if (auto SpawnPoint = Cast<UWheelSpawnPoint>(Child))
		{
			if (auto SprungWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor()))
			{
				Result.Add(SprungWheel);
			}
		}
	}
	return Result;
}

