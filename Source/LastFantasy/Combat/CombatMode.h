/**
*  Enables the combat mode
*  1. Set flag to pause all AI's
*  2. Blur everything in a certain radius
*/

#pragma once

#include "../Characters/BaseCharacter.h"
#include "../Characters/MainCharacter.h"
#include "../Enemy/BasicEnemy.h"
#include "Engine/StaticMeshActor.h"
#include "CombatMode.generated.h"


/**
 * 
 */
UCLASS()
class LASTFANTASY_API ACombatMode : public AStaticMeshActor
{
	GENERATED_BODY()

private:
	AMainCharacter* MainPlayerCharacter;

public:
	ACombatMode();
	void Enable();
	void BlurEnvironment();
	void Disable();
	void ClearBlurredEnvironment();
	void PlayCombatSound();
	void StopCombatSound();

private:

	void SetEnemiesToCombatMode();

//UFUNCTION
public:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

//UPROPERTY
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trigger")
		UBoxComponent* TriggerBox;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		TArray<ABasicEnemy*> Enemies;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
		TArray<ABaseCharacter*> Heroes;

};
