// Fill out your copyright notice in the Description page of Project Settings.

#include "LastFantasy.h"
#include "MainCharacter.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CombatCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CombatCamera"));
	CombatCamera->SetupAttachment(RootComponent);
	CombatCamera->bAutoActivate = false;

	CombatCameraTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CombatCameraTarget"));
	CombatCameraTarget->SetupAttachment(RootComponent);
	CombatCameraTarget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCameraTarget->bHiddenInGame = true;
}


void AMainCharacter::EnableCombatMode(TArray<ABasicEnemy*> Enemies)
{
	isCombatMode = true;
	Super::FocusEnemy(Enemies);
	CombatCamera->Activate();
	FollowCamera->Deactivate();
	DisableMovement();
}

void AMainCharacter::DisableCombatMode()
{
	isCombatMode = false;
	EnableMovement();
}

void AMainCharacter::EnableMovement()
{
	EnableWalkAnimation();
	GetCharacterMovement()->Activate();
}

void AMainCharacter::DisableMovement()
{
	DisableWalkAnimation();
	GetCharacterMovement()->Deactivate();
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetCombatCamera();
}

void AMainCharacter::SetCombatCamera()
{
	if (isCombatMode && cameraHasReachedLocation != true) {
		float interpSpeed = 1.0;
		FVector cameraVector = FMath::VInterpTo(CombatCamera->RelativeLocation, CombatCameraTarget->RelativeLocation, GetWorld()->GetDeltaSeconds(), interpSpeed);
		FRotator cameraRotator = FMath::RInterpTo(CombatCamera->RelativeRotation, CombatCameraTarget->RelativeRotation, GetWorld()->GetDeltaSeconds(), interpSpeed);
		CombatCamera->SetRelativeLocationAndRotation(cameraVector, cameraRotator);
		if (CombatCamera->RelativeLocation.Equals(CombatCameraTarget->RelativeLocation, 100))
		{
			cameraHasReachedLocation = true;
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);
}

void AMainCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}