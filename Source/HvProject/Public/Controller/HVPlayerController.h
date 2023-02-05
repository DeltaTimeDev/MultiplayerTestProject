// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HVPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HVPROJECT_API AHVPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	/*Possesing to vehicle. Should be called on server*/
	void GetInVehicle(class AHVVehicle* Vehicle, class AHVCharacter* CurrentCharacter);
	/*Possesing to character. Should be called on server*/
	void GetOutVehicle(class AHVVehicle* Vehicle);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHVCharacter> LastCharacterClass;

};
