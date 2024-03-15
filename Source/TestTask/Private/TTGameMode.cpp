// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TTBallActor.h"
#include "TTPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "TTPlayerState.h"

void ATTGameMode::OnPlayerScored(int32 PlayerIndex)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), PlayerIndex);
	if (PlayerController != nullptr)
	{
		ATTPlayerState* PlayerState = Cast<ATTPlayerState>(PlayerController->GetPlayerState<APlayerState>());
		if (PlayerState != nullptr)
		{
			PlayerState->SetScore(PlayerState->GetScore() + 1);
			PlayerState->UpdatePlayerScoreWidget();
		}
	}

	SpawnBall();
}

void ATTGameMode::StartMatch()
{
	AGameMode::StartMatch();

	if (HasAuthority())
	{
		SpawnBall();
		TriggerOnStartMatchEvent();
	}
}

void ATTGameMode::SpawnBall()
{
	if (CenterPositionActor != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			World->SpawnActor<ATTBallActor>(BallClass, CenterPositionActor->GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

void ATTGameMode::TriggerOnStartMatchEvent_Implementation()
{
	OnStartMatchEvent.Broadcast();
}

void ATTGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATTGameMode, OnStartMatchEvent);
}