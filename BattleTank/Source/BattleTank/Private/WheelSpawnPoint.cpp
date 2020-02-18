// Copyright reserved by Serhii D. 


#include "WheelSpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UWheelSpawnPoint::UWheelSpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWheelSpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//auto LeftTrackSocketTransform = GetAttachParent()->GetAttachParent()->GetSocketTransform(FName("LeftTrack"));
	//UE_LOG(LogTemp, Warning, TEXT("Spawn Point parent is %s"), *LeftTrackSocketLocation.ToString())
	auto SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorBP, GetComponentTransform());
	if (!SpawnedActor) return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void UWheelSpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

