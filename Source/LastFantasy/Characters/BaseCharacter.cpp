// Fill out your copyright notice in the Description page of Project Settings.

#include "LastFantasy.h"
#include "Enemy/BasicEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCharacter.h"

void ABaseCharacter::FocusEnemy(TArray<ABasicEnemy*> Enemies)
{
	if (isCombatMode == false) 
	{
		return;
	}

	if (Enemies.Num() == 0)
	{
		logError(TEXT("[Error] No enemy to focus"));
	}

	ABasicEnemy* Enemy = Enemies[0];
	const FVector CurrentLocation = GetActorLocation();
	const FVector AggressorLocation = Enemy->GetActorLocation();
	FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, AggressorLocation);
	FRotator AggressorRotation = FMath::Lerp(GetActorRotation(), LookRotation, 0.2f);
	SetActorRotation(AggressorRotation);
	FaceRotation(AggressorRotation);
}


void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// where to store the enemies?
	//FocusEnemy();
}