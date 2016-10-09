// Fill out your copyright notice in the Description page of Project Settings.

#include "LastFantasy.h"
#include "CombatMode.h"


ACombatMode::ACombatMode()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	TriggerBox->bGenerateOverlapEvents = true;
	SetActorEnableCollision(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACombatMode::OnOverlapBegin);	

	// Testing only
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACombatMode::OnOverlapEnd);
}


void ACombatMode::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MainPlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Enable();
}

void ACombatMode::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Disable();
}

void ACombatMode::Enable()
{
	debug(TEXT("EnableCombat Mode"));
	BlurEnvironment();

}

void ACombatMode::BlurEnvironment()
{
	
	if (MainPlayerCharacter != nullptr)
	{
		UCameraComponent* followCamera = MainPlayerCharacter->GetFollowCamera();
		FPostProcessSettings postProcessSettings;
		postProcessSettings.AutoExposureBias = -0.3;
		postProcessSettings.VignetteIntensity = 1;
		postProcessSettings.DepthOfFieldFocalDistance = 0;
		postProcessSettings.DepthOfFieldFocalRegion = 1000;
		postProcessSettings.DepthOfFieldMethod = EDepthOfFieldMethod::DOFM_Gaussian;
		postProcessSettings.bOverride_AutoExposureBias = true;
		postProcessSettings.bOverride_VignetteIntensity = true;
		postProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
		postProcessSettings.bOverride_DepthOfFieldFocalRegion = true;
		postProcessSettings.bOverride_DepthOfFieldMethod = true;
		followCamera->PostProcessSettings = postProcessSettings;
	}
	
}

void ACombatMode::Disable()
{
	debug(TEXT("Disable combat mode"));
	ClearBlurredEnvironment();
}

void ACombatMode::ClearBlurredEnvironment()
{
	if (MainPlayerCharacter != nullptr)
	{
		UCameraComponent* followCamera = MainPlayerCharacter->GetFollowCamera();
		FPostProcessSettings postProcessSettings;
		postProcessSettings.AutoExposureBias =  0.0 ;
		postProcessSettings.VignetteIntensity = 0.4;
		postProcessSettings.DepthOfFieldFocalDistance = 1000;
		postProcessSettings.DepthOfFieldFocalRegion = 0;
		postProcessSettings.bOverride_AutoExposureBias = true;
		postProcessSettings.bOverride_VignetteIntensity = true;
		postProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
		postProcessSettings.bOverride_DepthOfFieldFocalRegion = true;
		followCamera->PostProcessSettings = postProcessSettings;
	}
}