// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include <Components/TextBlock.h>
#include <Components/CanvasPanelSlot.h>


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	//��ġ X���� 500���� �ٲ���
	//slot �� ��������
	//UPanelSlot* slot = bestLevelUI->Slot;

	//Canvas panel slot ���� Cast ������
	//UCanvasPanelSlot* canvasSlot = Cast<UCanvasPanelSlot>(slot);

	//��ġ�� �ٲ���
	//canvasSlot->SetPosition(FVector2D(500, 108));
}


void UMainUI::UpdateCurrLevelUI(int32 score)
{
	//currScore �� text ���� score ������ �Ѵ�.
	currLevelUI->SetText(FText::AsNumber(score));
}

void UMainUI::UpdateBestLevelUI(int32 score)
{
	//bestScore �� text ���� score ������ �Ѵ�.
	bestLevelUI->SetText(FText::AsNumber(score));
}
