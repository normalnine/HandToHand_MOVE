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

	//mainUI 를 만든다
	mainUI = CreateWidget<UMainUI>(GetWorld(), mainWidget);

	//만든 UI를 Viewport에 붙힌다.
	mainUI->AddToViewport();

	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());

	//최고레벨을 세팅하자
	mainUI->UpdateBestLevelUI(bestLevel);
	mainUI->UpdateCurrLevelUI(hthGameInstance->stageLevel);

	//최고점수 불러오자
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
	//NextLevelUI 를 하나 만든다.
	NextLevelUI = CreateWidget<UNextLevelUI>(GetWorld(), NextLevelWidget);

	//만든 UI 를 화면에 띄운다.
	NextLevelUI->AddToViewport();	

	UGameplayStatics::SetGamePaused(GetWorld(), true);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void AHandToHand_MOVEGameMode::SaveBestLevel()
{
	//bestScore -> BestScoreData 에 있는 saveBestScore 변수에 넣는다

	//1. UBestScoreData 를 하나 생성한다. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::CreateSaveGameObject(UBestLevelData::StaticClass());

	//2. 생성한 놈을 UBestScoreData 로 Cast 하자
	UBestLevelData* bestLevelData = Cast<UBestLevelData>(saveGame);

	//3. saveBestScore = bestScore
	bestLevelData->saveBestLevel = bestLevel;

	//4. 저장한다
	UGameplayStatics::SaveGameToSlot(saveGame, TEXT("BEST_LEVEL"), 0);

}

void AHandToHand_MOVEGameMode::LoadBestLevel()
{
	//1. "BEST_SCORE" 으로 되어 있는 데이터를 불러온다. (USaveGame*)
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot(TEXT("BEST_LEVEL"), 0);

	//2. 불러온 놈을 UBestScoreData 로 Cast 하자
	UBestLevelData* bestScoreData = Cast<UBestLevelData>(saveGame);

	//만약에 bestScoreData 가 nullptr 이 아니라면
	if (bestScoreData != nullptr)
	{
		//3. bestScore = saveBestScore
		bestLevel = bestScoreData->saveBestLevel;

		//4. BestScore UI 를 갱신한다.
		mainUI->UpdateBestLevelUI(bestLevel);
	}
}