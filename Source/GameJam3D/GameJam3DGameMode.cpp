// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameJam3DGameMode.h"
#include "GameJam3DCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameJam3DGameMode::AGameJam3DGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
