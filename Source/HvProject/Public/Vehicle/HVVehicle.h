// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "InputActionValue.h"
#include "HVVehicle.generated.h"

/**
 * 
 */
UCLASS()
class HVPROJECT_API AHVVehicle : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** GetOut Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* UseInteractableAction;
	
	/** Throttle Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* VehicleThrottleAction;
	
	/** ReverseBrake Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* VehicleReverseBrakeAction;

	/** Steering Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* VehicleSteeringAction;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	/** Called for movement input */
	void Throttle(const FInputActionValue& Value);

	/** Called for movement input */
	void ThrottleFinish(const FInputActionValue& Value);

	/** Called for movement input */
	void ReverseBrake(const FInputActionValue& Value);

	/** Called for movement input */
	void ReverseBrakeFinish(const FInputActionValue& Value);

	/** Called for Streeing input */
	void Streeing(const FInputActionValue& Value);

	/** Called for Streeing input */
	void StreeingFinish(const FInputActionValue& Value);
	
	UPROPERTY(Replicated)
	bool IsUsing = false;

public:
	/*Client command that calling server func for unposses of vehicle*/
	void GetOutVehicle();

	/*Server function that make vehicle unposses process*/
	UFUNCTION(Server, Reliable)
	void GetOutVehicleServer();

	bool IsAvailableForUse();
};
