// Copyright reserved by Serhii D. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	Empty
};
// Forward Declarations
class UTankBarrel; 
class UTankTurret;
class AProjectile;

/**
* Responsible for aiming and lunchung a projectile
*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, category = Setup)
	void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Mechanics)
	void Fire();

	void AimAt(FVector HitLocation);

	EAimingStatus GetAimingStatus() const;

	UFUNCTION(BlueprintCallable, Category = UI)
	int32 GetAmmo() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, category = State)
	EAimingStatus AimingStatus = EAimingStatus::Reloading;

	

private:
	void MoveBarrelTowards(FVector AimDirection);
	bool bIsBarrelMoving();
	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	FVector AimDirection = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 Ammo = 3;



	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0;
	double LastFireTime = 0;
};
