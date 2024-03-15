// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTBallActor.generated.h"

UCLASS()
class TESTTASK_API ATTBallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATTBallActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* BallMesh;

	UPROPERTY(EditAnywhere, Category = "Collider")
	class USphereComponent* BallCollider;

	UPROPERTY(EditAnywhere, Category = "StartSpeed")
	float MoveSpeed;
	FVector CurrentMoveDirection;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;
};