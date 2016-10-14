// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/BaseCharacter.h"
#include "Enemy/BasicEnemy.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LASTFANTASY_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CombatCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* CombatCameraTarget;



private:
	bool cameraHasReachedLocation = false;
	TArray<ABasicEnemy*> Enemies;
	void SetCombatCamera();

public:
	// Sets default values for this character's properties
	AMainCharacter();

	void EnableCombatMode(TArray<ABasicEnemy*> Enemies);
	void DisableCombatMode();
	void EnableMovement();
	void DisableMovement();
	void Tick(float DeltaTime) override;


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	// event to stop walk animation in BP
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "disableWalkAnimation"), Category = "Movement")
		void DisableWalkAnimation();

	// event to stop walk animation in BP
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "enableWalkAnimation"), Category = "Movement")
		void EnableWalkAnimation();

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UCameraComponent* GetCombatCamera() const { return CombatCamera; }
	
};
