// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	//위치 X값만 500으로 바꾸자
	//slot 을 가져오자
	//UPanelSlot* slot = bestLevelUI->Slot;

	//Canvas panel slot 으로 Cast 해주자
	//UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

	//위치를 바꾸자
	//canvasSlot->SetPosition(FVector2D(500, 108));
}


void UMainUI::UpdateCurrLevelUI(int32 score)
{
	//currScore 의 text 값을 score 값으로 한다.
	currLevelUI->SetText(FText::AsNumber(score));
}

void UMainUI::UpdateBestLevelUI(int32 score)
{
	//bestScore 의 text 값을 score 값으로 한다.
	bestLevelUI->SetText(FText::AsNumber(score));
}
