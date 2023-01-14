// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* currLevelUI;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* bestLevelUI;

public:
	void UpdateCurrLevelUI(int32 score);
	void UpdateBestLevelUI(int32 score);
};
