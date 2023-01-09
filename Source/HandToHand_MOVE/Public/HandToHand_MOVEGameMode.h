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

public:
	UPROPERTY(EditAnywhere)
	int32 stageLevel;

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

	UFUNCTION()
	void ShowNextLevel();
};



