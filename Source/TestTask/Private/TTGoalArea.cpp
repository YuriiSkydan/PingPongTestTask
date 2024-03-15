// Fill out your copyright notice in the Description page of Project Settings.


#include "TTGoalArea.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TTBallActor.h"
#include "TTGameMode.h"

// Sets default values
ATTGoalArea::ATTGoalArea()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATTGoalArea::OnOverlapBegin);
}

void ATTGoalArea::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (Cast<ATTBallActor>(OtherActor) != nullptr)
		{
			OtherActor->Destroy();
		}

		ATTGameMode* GameMode = Cast<ATTGameMode>(UGameplayStatics::GetGameMode(this));
		if (GameMode != nullptr)
		{
			GameMode->OnPlayerScored(ScoredPlayer);
		}
	}
}