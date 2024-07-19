// Copyright Epic Games, Inc. All Rights Reserved.

#include "OSSGameMode.h"
#include "OSSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOSSGameMode::AOSSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
