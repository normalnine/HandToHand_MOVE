// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuUI.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UStartMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 바인딩
	btnStart->OnClicked.AddDynamic(this, &UStartMenuUI::Start);
	btnQuit->OnClicked.AddDynamic(this, &UStartMenuUI::Quit);

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

void UStartMenuUI::Start()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("KDH_ThirdPersonMap"));
}
void UStartMenuUI::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
