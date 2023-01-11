// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BestLevelData.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UBestLevelData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 saveBestLevel;
};
