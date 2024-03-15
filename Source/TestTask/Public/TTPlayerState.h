// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TTPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ATTPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	virtual void OnRep_Score() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerScoreWidget();
};
