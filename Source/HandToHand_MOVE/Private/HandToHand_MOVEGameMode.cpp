// Copyright Epic Games, Inc. All Rights Reserved.

#include "HandToHand_MOVEGameMode.h"
#include "HandToHand_MOVECharacter.h"
#include "UObject/ConstructorHelpers.h"

AHandToHand_MOVEGameMode::AHandToHand_MOVEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/KEJ/Blueprints/BP_PlayerPawn.BP_PlayerPawn_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
