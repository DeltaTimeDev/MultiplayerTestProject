// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/HVPlayerController.h"
#include "Character/HVCharacter.h"
#include "Vehicle/HVVehicle.h"

void AHVPlayerController::GetInVehicle(AHVVehicle* Vehicle, AHVCharacter* CurrentCharacter)
{
	Possess(Vehicle);
	LastCharacterClass = CurrentCharacter->GetClass();
	CurrentCharacter->Destroy();
}

void AHVPlayerController::GetOutVehicle(AHVVehicle* Vehicle)
{
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector Location = Vehicle->GetActorLocation() + Vehicle->GetActorRightVector() * -150 + FVector(0, 0, 200);

	AHVCharacter* SpawnedCharacter = GetWorld()->SpawnActor<AHVCharacter>(LastCharacterClass, Location, Vehicle->GetActorForwardVector().Rotation(), Parameters);
	if (SpawnedCharacter)
	{
		Possess(SpawnedCharacter);
	}
}

