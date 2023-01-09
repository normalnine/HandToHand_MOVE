// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NextLevelUI.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UNextLevelUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnNext;

	UPROPERTY()
	class UHTH_GameInstance* hthGameInstance;

	UFUNCTION()
	void NextLevel();
};
