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
	
	if (Heroes.Num() == 0) {
		logError(TEXT("No hero has been set"));
	}

	// Testing only
	//TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACombatMode::OnOverlapEnd);
}


void ACombatMode::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MainPlayerCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Enable();
}

void ACombatMode::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Disable();
}

void ACombatMode::Enable()
{
	PlayCombatSound();
	MainPlayerCharacter->EnableCombatMode();
	BlurEnvironment();
	SetEnemiesToCombatMode();
}

void ACombatMode::SetEnemiesToCombatMode()
{
	ABasicEnemy* Enemy = nullptr;
	for (int i = 0; i < Enemies.Num(); i++) {
		Enemy = Enemies[i];
		Enemy->SetActiveAggressors(Heroes);
		Enemy->EnableCombatMode();
	}
	delete Enemy;
}

void ACombatMode::BlurEnvironment()
{
	if (MainPlayerCharacter != nullptr)
	{
		UCameraComponent* followCamera = MainPlayerCharacter->GetCombatCamera();
		FPostProcessSettings postProcessSettings;
		postProcessSettings.AutoExposureBias = -0.2;
		postProcessSettings.VignetteIntensity = 1;
		postProcessSettings.DepthOfFieldFocalDistance = 0;
		postProcessSettings.DepthOfFieldFocalRegion = 1200;
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
	StopCombatSound();
	MainPlayerCharacter->DisableCombatMode();
	ClearBlurredEnvironment();
}

void ACombatMode::ClearBlurredEnvironment()
{
	if (MainPlayerCharacter != nullptr)
	{
		UCameraComponent* followCamera = MainPlayerCharacter->GetCombatCamera();
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

void ACombatMode::PlayCombatSound()
{
}

void ACombatMode::StopCombatSound()
{
}
