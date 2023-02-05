// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/HVVehicle.h"
#include "ChaosVehicleMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Controller/HVPlayerController.h"
#include "Controller/HVPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void AHVVehicle::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AHVVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		//Interact_Use
		EnhancedInputComponent->BindAction(UseInteractableAction, ETriggerEvent::Started, this, &AHVVehicle::GetOutVehicle);
		
		//Moving
		EnhancedInputComponent->BindAction(VehicleThrottleAction, ETriggerEvent::Triggered, this, &AHVVehicle::Throttle);
		EnhancedInputComponent->BindAction(VehicleThrottleAction, ETriggerEvent::Completed, this, &AHVVehicle::ThrottleFinish);

		EnhancedInputComponent->BindAction(VehicleReverseBrakeAction, ETriggerEvent::Triggered, this, &AHVVehicle::ReverseBrake);
		EnhancedInputComponent->BindAction(VehicleReverseBrakeAction, ETriggerEvent::Completed, this, &AHVVehicle::ReverseBrakeFinish);

		EnhancedInputComponent->BindAction(VehicleSteeringAction, ETriggerEvent::Triggered, this, &AHVVehicle::Streeing);
		EnhancedInputComponent->BindAction(VehicleSteeringAction, ETriggerEvent::Completed, this, &AHVVehicle::StreeingFinish);
	}
}


void AHVVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHVVehicle, IsUsing);
}

void AHVVehicle::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (Cast<AHVPlayerController>(NewController))
	{
		IsUsing = true;
	}
}

void AHVVehicle::UnPossessed()
{
	Super::UnPossessed();

	IsUsing = false;
}

void AHVVehicle::Throttle(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(1);
}

void AHVVehicle::ThrottleFinish(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(0);
}

void AHVVehicle::ReverseBrake(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(1);
}

void AHVVehicle::ReverseBrakeFinish(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(0);
}

void AHVVehicle::Streeing(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	GetVehicleMovementComponent()->SetSteeringInput(MovementValue);
}

void AHVVehicle::StreeingFinish(const FInputActionValue& Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(0);
}

void AHVVehicle::GetOutVehicle()
{
	GetOutVehicleServer();
}

void AHVVehicle::GetOutVehicleServer_Implementation()
{
	if (Cast<AHVPlayerController>(GetController()))
	{
		Cast<AHVPlayerController>(GetController())->GetOutVehicle(this);
	}
}

bool AHVVehicle::IsAvailableForUse()
{
	return !IsUsing;
}
