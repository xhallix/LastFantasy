// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#ifndef __LASTFANTASY_H__
#define __LASTFANTASY_H__

#include "Engine.h"

#define debug(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Blue,text)
#define logError(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red,text)


#endif
