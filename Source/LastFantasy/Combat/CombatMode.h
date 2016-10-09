/**
*  Enables the combat mode
*  1. Set flag to pause all AI's
*  2. Blur everything in a certain radius
*/

#pragma once

#include "../Characters/BaseCharacter.h"
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
	ABaseCharacter* MainPlayerCharacter;

public:
	ACombatMode();
	void Enable();
	void BlurEnvironment();
	void Disable();
	void ClearBlurredEnvironment();


//UFUNCTION
public:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

//UPROPERTY
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Trigger")
		UBoxComponent* TriggerBox;
	
};
