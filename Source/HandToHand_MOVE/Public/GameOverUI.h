// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	//BeginPlay 와 같은 동작
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btnRetry;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* btnQuit;

public:
	UFUNCTION()
		void Retry();

	UFUNCTION()
		void Quit();
};
