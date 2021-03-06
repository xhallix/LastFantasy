// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

// FWD declaration
class ABasicEnemy;

UCLASS()
class LASTFANTASY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()


protected:
	void Tick(float DeltaTime);


public:
	void EnableCombatMode() {};
	void DisableCombatMode() {};
	void FocusEnemy(TArray<ABasicEnemy*> Enemies);
	bool isCombatMode = false;
	class UCameraComponent* CombatCamera;
	FORCEINLINE class UCameraComponent* GetCombatCamera() const { return CombatCamera; }
	
};
