// Copyright Epic Games, Inc. All Rights Reserved.

#include "HandToHand_MOVEGameMode.h"
#include "HandToHand_MOVECharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "NextLevelUI.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerController.h>
#include "HTH_GameInstance.h"
#include <Engine/GameInstance.h>
#include "MainUI.h"
#include "BestLevelData.h"

AHandToHand_MOVEGameMode::AHandToHand_MOVEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Blueprint'/Game/KDH/Enemy/Bluprints/BP_PlayerPawn.BP_PlayerPawn_C'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UMainUI> tempMainUI(TEXT("WidgetBlueprint'/Game/KDH/UI/BP_MainUI.BP_MainUI_C'"));
	if (tempMainUI.Succeeded())
	{
		mainWidget = tempMainUI.Class;
	}

	ConstructorHelpers::FClassFinder<UNextLevelUI> tempNextLevelUI(TEXT("WidgetBlueprint'/Game/KDH/UI/BP_NextLevelUI.BP_NextLevelUI_C'"));
	if (tempNextLevelUI.Succeeded())
	{
		NextLevelWidget = tempNextLevelUI.Class;
	}
}

void AHandToHand_MOVEGameMode::BeginPlay()
{
	Super::BeginPlay();

	//mainUI �� �����
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);

	//���� UI�� Viewport�� ������.
	mainUI->AddToViewport();

	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());

	//�ְ����� ��������
	mainUI->UpdateBestLevelUI(bestLevel);
	mainUI->UpdateCurrLevelUI(hthGameInstance->stageLevel);

	//�ְ����� �ҷ�����
	LoadBestLevel();

	if (hthGameInstance->stageLevel > bestLevel)
	{
		bestLevel = hthGameInstance->stageLevel;
		mainUI->UpdateBestLevelUI(bestLevel);
		SaveBestLevel();
	}
}


void AHandToHand_MOVEGameMode::ShowNextLevel()
{
	//NextLevelUI �� �ϳ� �����.
	NextLevelUI = CreateWidget<UNextLevelUI>(GetWorld(), NextLevelWidget);

	//���� UI �� ȭ�鿡 ����.
	NextLevelUI->AddToViewport();	

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void AHandToHand_MOVEGameMode::SaveBestLevel()
{
	//bestScore -> BestScoreData �� �ִ� saveBestScore ������ �ִ´�

	//1. UBestScoreData �� �ϳ� �����Ѵ�. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UBestLevelData::StaticClass());

	//2. ������ ���� UBestScoreData �� Cast ����
	UBestLevelData* bestLevelData = Cast<UBestLevelData>(saveGame);

	//3. saveBestScore = bestScore
	bestLevelData->saveBestLevel = bestLevel;

	//4. �����Ѵ�
	UGameplayStatics::SaveGameToSlot(saveGame, TEXT("BEST_LEVEL"), 0);

}

void AHandToHand_MOVEGameMode::LoadBestLevel()
{
	//1. "BEST_SCORE" ���� �Ǿ� �ִ� �����͸� �ҷ��´�. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_LEVEL"), 0);

	//2. �ҷ��� ���� UBestScoreData �� Cast ����
	UBestLevelData* bestScoreData = Cast<UBestLevelData>(saveGame);

	//���࿡ bestScoreData �� nullptr �� �ƴ϶��
	if (bestScoreData != nullptr)
	{
		//3. bestScore = saveBestScore
		bestLevel = bestScoreData->saveBestLevel;

		//4. BestScore UI �� �����Ѵ�.
		mainUI->UpdateBestLevelUI(bestLevel);
	}
}