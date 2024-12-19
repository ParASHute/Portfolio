// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortfolioGameMode.h"
#include "PortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortfolioGameMode::APortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/02_characters/BP_BaseCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
