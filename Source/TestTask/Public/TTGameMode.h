// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TTGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartMatch);

/**
 * 
 */
UCLASS()
class TESTTASK_API ATTGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerScored(int32 PlayerIndex);

protected:
	virtual void StartMatch() override;

	UFUNCTION(BlueprintCallable)
	void SpawnBall();

	UFUNCTION(Server, Reliable)
	void TriggerOnStartMatchEvent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintAssignable, Replicated)
	FOnStartMatch OnStartMatchEvent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* CenterPositionActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATTBallActor> BallClass;
};