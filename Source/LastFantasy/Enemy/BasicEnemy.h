// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "../Characters/BaseCharacter.h"
#include "BasicEnemy.generated.h"


UCLASS()
class LASTFANTASY_API ABasicEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// health
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		int Health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		int Exp = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		int Mana = 100;

	// money
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		int Lig = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		int Speed = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterAttributes")
		AActor* DropableItem;

public:
	
	void EnableCombatMode();	
	void SetActiveAggressors(TArray<ABaseCharacter*> Aggressor);


private:

	struct AttackInformation {ABaseCharacter* Aggressor; int Rage;};
	TArray<AttackInformation> AggressorsInformation;

	// The aggressor which causes most rage
	ABaseCharacter* MainAggressor;

private:
	void FocusAggressor();
	void SetAggressorByRage();
	void SetMainPlayerCharacterAsAggressor();


};
