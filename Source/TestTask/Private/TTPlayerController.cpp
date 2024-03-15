// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPlayerController.h"
#include "TTPlayerPlatform.h"

void ATTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MovePlatform", this, &ATTPlayerController::MovePlatform);
}

void ATTPlayerController::MovePlatform(float AxisValue)
{
	ATTPlayerPlatform* ControlledPlatform = Cast<ATTPlayerPlatform>(GetPawn());
	if (ControlledPlatform != nullptr)
	{
		ControlledPlatform->Move(AxisValue);
	}
}