// Copyright reserved by Serhii D. 


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);
	
	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);

	Roller = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Roller"));
	Roller->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnCompHit);
	// TODO move to a seperate function with adding reference checking
	Spring->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()), NAME_None, Axle, NAME_None);
	Roller->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ensure(Wheel))
	{
		Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ForceMagnitude = 0;
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	this->ForceMagnitude += ForceMagnitude;
}


