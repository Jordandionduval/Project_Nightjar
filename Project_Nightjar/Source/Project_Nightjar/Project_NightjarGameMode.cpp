// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_NightjarGameMode.h"
#include "Project_NightjarCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_NightjarGameMode::AProject_NightjarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
