// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class LASTFANTASY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	void EnableCombatMode() {};
	void DisableCombatMode() {};

	class UCameraComponent* CombatCamera;

	FORCEINLINE class UCameraComponent* GetCombatCamera() const { return CombatCamera; }
	
};
