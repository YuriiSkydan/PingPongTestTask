// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Net/UnrealNetwork.h"
#include "TTPlayerPlatform.generated.h"

UCLASS()
class TESTTASK_API ATTPlayerPlatform : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATTPlayerPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Move(float AxisValue);

	UFUNCTION(Server, Reliable)
	void UpdateLocation(FVector Location);

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PlayerPlatformMesh;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float MaxDistanceFromStart;

	FVector StartLocation;
};
