// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPlayerPlatform.h"

// Sets default values
ATTPlayerPlatform::ATTPlayerPlatform()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerPlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlayerPlatformMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATTPlayerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
}

void ATTPlayerPlatform::Move(float AxisValue)
{
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorRightVector() * MoveSpeed * AxisValue * GetWorld()->DeltaTimeSeconds;
	 
	float Distance = FVector::Distance(NewLocation, StartLocation);
	if (Distance > MaxDistanceFromStart)
	{
		NewLocation = StartLocation + GetActorRightVector() * MaxDistanceFromStart * AxisValue;
	}
	
	SetActorLocation(NewLocation);
	UpdateLocation(NewLocation);
}

void ATTPlayerPlatform::UpdateLocation_Implementation(FVector Location)
{
	SetActorLocation(Location);
}