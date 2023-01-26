// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>
#include <Kismet/KismetSystemLibrary.h>
#include "HTH_GameInstance.h"

void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	//btnRetry Ŭ�� �� Retry �Լ� ����
	btnRetry->OnClicked.AddDynamic(this, &UGameOverUI::Retry);

	//btnQuit Ŭ�� �� Quit �Լ� ����
	btnQuit->OnClicked.AddDynamic(this, &UGameOverUI::Quit);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UGameOverUI::Retry()
{
	//������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("DemoMap1"));
	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());
	if (hthGameInstance != nullptr)
	{
		hthGameInstance->stageLevel = 1;
	}
}
void UGameOverUI::Quit()
{
	//������ ���� ��Ų��.
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}