// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelUI.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Button.h>
#include "HTH_GameInstance.h"
#include <Engine/GameInstance.h>
#include <Sound/SoundBase.h>



void UNextLevelUI::NativeConstruct()
{
	Super::NativeConstruct();

	//btnRetry 클릭 시 Retry 함수 연결
	btnNext->OnClicked.AddDynamic(this, &UNextLevelUI::NextLevel);
}

void UNextLevelUI::NextLevel()
{
	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());
	if (hthGameInstance != nullptr)
	{
		hthGameInstance->stageLevel++;
	}
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("DemoMap1"));
}