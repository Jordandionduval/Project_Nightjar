// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_NightjarGameMode.h"
#include "Project_NightjarCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_NightjarGameMode::AProject_NightjarGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
