// Copyright reserved by Serhii D. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.generated.h"


UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Apply force to drive a wheel, positive value respons to forward move and negative to backwards
	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Spring = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Roller = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel = nullptr;

	float ForceMagnitude;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
