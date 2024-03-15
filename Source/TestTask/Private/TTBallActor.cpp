// Fill out your copyright notice in the Description page of Project Settings.


#include "TTBallActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATTBallActor::ATTBallActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(RootComponent);
	BallMesh->OnComponentHit.AddDynamic(this, &ATTBallActor::OnHit);
}

// Called when the game starts or when spawned
void ATTBallActor::BeginPlay()
{
	Super::BeginPlay();
	
	//CurrentVelocity = InitialVelocity;
	CurrentMoveDirection = FVector(FMath::RandPointInCircle(1.0f), 0.0f);
	CurrentMoveDirection.Normalize();
	FVector NewVelocity = CurrentMoveDirection * MoveSpeed;
	BallMesh->SetPhysicsLinearVelocity(NewVelocity);
}

// Called every frame
void ATTBallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Velocity = CurrentMoveDirection * MoveSpeed;
		BallMesh->SetPhysicsLinearVelocity(Velocity);
	}
}

void ATTBallActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	if (HasAuthority())
	{
		float Dot = FVector::DotProduct(CurrentMoveDirection, Hit.Normal);
		if (Dot < 0.0f)
		{
			FVector NewMoveDirection = FMath::GetReflectionVector(CurrentMoveDirection, Hit.Normal);
			NewMoveDirection.Z = 0;
			NewMoveDirection.Normalize();
			CurrentMoveDirection = NewMoveDirection;
			FVector NewVelocity = CurrentMoveDirection * MoveSpeed;
			BallMesh->SetPhysicsLinearVelocity(NewVelocity);
		}
	}
}