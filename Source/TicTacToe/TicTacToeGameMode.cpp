// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeGameMode.h"
#include "TicTacToeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATicTacToeGameMode::ATicTacToeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
