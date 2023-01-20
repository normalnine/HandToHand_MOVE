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

	// ���Ӹ�� ĳ����
	currGameMode = Cast<AHandToHand_MOVEGameMode>(GetWorld()->GetAuthGameMode());

	hthGameInstance = Cast<UHTH_GameInstance>(GetWorld()->GetGameInstance());
	if (hthGameInstance != nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("currlevel %d"), hthGameInstance->stageLevel);
	}

	// ���� ��ġ ���� �Ҵ�
	FindSpawnPoints();

	enemyNumFactory = currGameMode->allEnemyNum;

	// 1. ���� ���� �ð� ���ϱ�
	float createTime = FMath::RandRange(minTime, maxTime);

	// 2. Timer Manager ���� �˶� ���
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);	

	// �׻� �����ǰ� ����
	spawParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

void AEnemyManager::CreateEnemy()
{
	// ���� ��ġ ���ϱ�
	int index = FMath::RandRange(0, spawnPoints.Num() - 1);	

	// �� ���� �� ��ġ�ϱ�
	GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(0), spawParam);

	// �� ������ �� ī��Ʈ �ϱ�
	enemySpawnCounter++;
	UE_LOG(LogTemp,Warning,TEXT("%d beonjje"), enemySpawnCounter);

	// ���� �� ���������� �׸� �����ϱ�
	if (enemySpawnCounter >= enemyNumFactory) return;

	// �ٽ� ���� �ð��� CreateEnemy �Լ��� ȣ��ǵ��� Ÿ�̸� ����
	float createTime = FMath::RandRange(minTime, maxTime);
	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
}

void AEnemyManager::FindSpawnPoints()
{
	// �˻����� ã�� ����� ������ �迭
	TArray<AActor*> allActors;

	// ���ϴ� Ÿ���� ���� ��� ã�ƿ���
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	
	// ã�� ����� ���� ��� �ݺ�������
	for (auto spawn : allActors)
	{
		// ã�� ������ �̸��� �ش� ���ڿ��� �����ϰ� �ִٸ�
		if (spawn->GetName().Contains(TEXT("EnemySpawnPoint")))
		{
			// ���� ��Ͽ� �߰�
			spawnPoints.Add(spawn);			
		}
	}	
	currGameMode->allEnemyNum = hthGameInstance->stageLevel * spawnPoints.Num();
}