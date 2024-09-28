// Copyright Epic Games, Inc. All Rights Reserved.

#include "InventoryTestGameMode.h"
#include "InventoryTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInventoryTestGameMode::AInventoryTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
