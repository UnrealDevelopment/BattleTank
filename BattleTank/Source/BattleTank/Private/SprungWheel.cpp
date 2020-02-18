// Copyright reserved by Serhii D. 


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);
	
	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);

	Roller = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Roller"));
	Roller->AttachToComponent(Axel, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("FUCKINGWHEELTHATISDISPLAYED"));
	Wheel->AttachToComponent(Roller, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	Spring->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()), NAME_None, Axel, NAME_None);
	Roller->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

