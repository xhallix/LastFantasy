// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "LastFantasy.h"
#include "LastFantasyGameMode.h"
#include "LastFantasyCharacter.h"

ALastFantasyGameMode::ALastFantasyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Playable/MainCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
