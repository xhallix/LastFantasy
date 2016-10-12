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

}


void ABasicEnemy::EnableCombatMode()
{
	FocusAggressor();
}


void ABasicEnemy::SetActiveAggressors(ABaseCharacter* Aggressor)
{
	Aggressors.Add(Aggressor);
}


void ABasicEnemy::FocusAggressor()
{
	if (Aggressors.Num() == 0)
	{
		debug(TEXT("[ERROR] Missing Aggressors"));
	}
	int RndNum = rand() % (Aggressors.Num() - 0 + 1) + 0;
	const FVector CurrentLocation = GetActorLocation();
	ABaseCharacter* Aggressor = Aggressors[RndNum];
	const FVector AggressorLocation = Aggressor->GetActorLocation();
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, AggressorLocation);
	SetActorRotation(FMath::Lerp(GetActorRotation(), LookRotation, 0.2f));
}
