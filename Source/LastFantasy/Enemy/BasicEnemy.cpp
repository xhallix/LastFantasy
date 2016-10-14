// Fill out your copyright notice in the Description page of Project Settings.

#include "LastFantasy.h"
#include "Kismet/KismetMathLibrary.h"
#include "BasicEnemy.h"


// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (IsInCombat)
	{
		FocusAggressor();
	}
}


void ABasicEnemy::EnableCombatMode()
{
	IsInCombat = true;
	FocusAggressor();
}


void ABasicEnemy::SetActiveAggressors(TArray<ABaseCharacter*> Aggressors)
{
	for (int i = 0; i < Aggressors.Num(); i++) {
		AttackInformation Info;
		Info.Aggressor = Aggressors[i];
		Info.Rage = 1;
		AggressorsInformation.Add(Info);
	}
}


void ABasicEnemy::FocusAggressor()
{
	if (AggressorsInformation.Num() == 0)
	{
		logError(TEXT("[ERROR] Missing Aggressors"));
		return;
	}

	SetAggressorByRage();
	const FVector CurrentLocation = GetActorLocation();
	const FVector AggressorLocation = MainAggressor->GetActorLocation();
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, AggressorLocation);
	FRotator AggressorRotation = FMath::Lerp(GetActorRotation(), LookRotation, 0.2f);
	SetActorRotation(AggressorRotation);
}

void ABasicEnemy::SetAggressorByRage()
{
	if (AggressorsInformation.Num() == 1) 
	{
		MainAggressor = AggressorsInformation[0].Aggressor;
		return;
	}
	int HighestRage = 0;
	for (int i = 0; i < AggressorsInformation.Num(); i++) {
	
		if (AggressorsInformation[i].Rage > HighestRage)
		{
			HighestRage = AggressorsInformation[i].Rage;
			MainAggressor = AggressorsInformation[i].Aggressor;
		}
	}

}


