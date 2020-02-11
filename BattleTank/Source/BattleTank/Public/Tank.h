// Copyright reserved by Serhii D. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// returnts health percent 0 to 1
	UFUNCTION(BlueprintPure, Category = "Mechanics")
	float GetHealthPercent() const; 

	
	FTankDelegate OnDeathEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mechanics")
	int32 HealthPoints = 100.0;

	UPROPERTY(VisibleAnywhere, Category = "Mechanics")
	int32 CurrentHealth = HealthPoints;
};