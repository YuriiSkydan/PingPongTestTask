// Fill out your copyright notice in the Description page of Project Settings.


#include "TTPlayerState.h"
#include "Kismet/GameplayStatics.h"

void ATTPlayerState::OnRep_Score()
{
	UpdatePlayerScoreWidget();
}