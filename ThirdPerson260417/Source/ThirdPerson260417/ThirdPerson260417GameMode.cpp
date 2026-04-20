// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPerson260417GameMode.h"
#include "ThirdPerson260417Character.h"
#include "UObject/ConstructorHelpers.h"

AThirdPerson260417GameMode::AThirdPerson260417GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
