// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HandToHand_MOVEGameMode.generated.h"

UCLASS(minimalapi)
class AHandToHand_MOVEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHandToHand_MOVEGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	int32 allEnemyNum;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainUI> mainWidget;

	UPROPERTY()
	class UMainUI* mainUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNextLevelUI> NextLevelWidget;

	UPROPERTY()
	class UNextLevelUI* NextLevelUI;

	UPROPERTY()
	class UHTH_GameInstance* hthGameInstance;

	int32 currLevel = 0;
	int32 bestLevel = 0;

	UFUNCTION()
	void ShowNextLevel();
	void SaveBestLevel();
	void LoadBestLevel();
	void ShowGameOverUI();
};



