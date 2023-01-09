// Copyright Epic Games, Inc. All Rights Reserved.

#include "HandToHand_MOVEGameMode.h"
#include "HandToHand_MOVECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "NextLevelUI.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>
#include "HTH_GameInstance.h"
#include <Engine/GameInstance.h>

AHandToHand_MOVEGameMode::AHandToHand_MOVEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/KDH/Enemy/Bluprints/BP_PlayerPawn.BP_PlayerPawn_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UNextLevelUI> tempNextLevelUI(TEXT("WidgetBlueprint'/Game/KDH/UI/BP_NextLevelUI.BP_NextLevelUI_C'"));
	if (tempNextLevelUI.Succeeded())
	{
		NextLevelWidget = tempNextLevelUI.Class;
	}
}

void AHandToHand_MOVEGameMode::ShowNextLevel()
{
	//NextLevelUI �� �ϳ� �����.
	NextLevelUI = CreateWidget<UNextLevelUI>(GetWorld(), NextLevelWidget);

	//���� UI �� ȭ�鿡 ����.
	NextLevelUI->AddToViewport();	
}
