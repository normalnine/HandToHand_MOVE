// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HTH_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UHTH_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int32 stageLevel = 1;
};
