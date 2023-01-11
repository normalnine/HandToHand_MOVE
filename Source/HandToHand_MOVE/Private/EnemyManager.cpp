// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"
#include <EngineUtils.h>
#include <Kismet/GamePlayStatics.h>
#include "EnemyAnim.h"
#include "EnemyFSM.h"
#include "Enemy.h"
#include "HandToHand_MOVEGameMode.h"
#include "HTH_GameInstance.h"
#include <Engine/EngineTypes.h>


// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();	

	// 게임모드 캐스팅
	currGameMode = Cast<AHandToHand_MOVEGameMode>(GetWorld()->GetAuthGameMode());

	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());
	if (hthGameInstance != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("currlevel %d"), hthGameInstance->stageLevel);
	}

	// 스폰 위치 동적 할당
	FindSpawnPoints();

	// 1. 랜덤 생성 시간 구하기
	float createTime = FMath::RandRange(minTime, maxTime);

	// 2. Timer Manager 한테 알람 등록
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);	

	// 항상 스폰되게 설정
	spawParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void AEnemyManager::CreateEnemy()
{
	// 랜덤 위치 구하기
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);	

	// 적 생성 및 배치하기
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0), spawParam);

	// 적 생성된 수 카운트 하기
	enemySpawnCounter++;
	UE_LOG(LogTemp,Warning,TEXT("%d 번째 적 생성"), enemySpawnCounter);

	// 적을 다 생성했으면 그만 생성하기
	if (enemySpawnCounter >= currGameMode->allEnemyNum) return;

	// 다시 랜덤 시간에 CreateEnemy 함수가 호출되도록 타이머 설정
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	// 검색으로 찾은 결과를 저장할 배열
	TArray<AActor*> allActors;

	// 원하는 타입의 액터 모두 찾아오기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);

	// 찾은 결과가 있을 경우 반복적으로
	for (auto spawn : allActors)
	{
		// 찾은 액터의 이름에 해당 문자열을 포함하고 있다면
		if (spawn->GetName().Contains(TEXT("EnemySpawnPoint")))
		{
			// 스폰 목록에 추가
			spawnPoints.Add(spawn);			
		}
	}	
	currGameMode->allEnemyNum = hthGameInstance->stageLevel * spawnPoints.Num();
}