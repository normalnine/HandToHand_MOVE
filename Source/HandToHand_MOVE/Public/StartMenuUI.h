// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UStartMenuUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;	

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnStart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* btnQuit;

	UFUNCTION()
	void Start();

	UFUNCTION()
	void Quit();
};
