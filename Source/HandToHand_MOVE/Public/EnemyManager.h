// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class HANDTOHAND_MOVE_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 랜덤 시간 간격 최솟값
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	float minTime = 1;

	// 랜덤 시간 간격 최댓값
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	float maxTime = 2;

	UPROPERTY(EditAnywhere)
	int32 enemySpawnCounter = 0;

	// 스폰할 위치 정보 배열
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<class AActor*> spawnPoints;

	// AEnemy 타입의 블루프린트 할당받은 변수
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TSubclassOf<class AEnemy> enemyFactory;

	// 스폰을 위한 알람 타이머
	FTimerHandle spawnTimerHandle;

	UPROPERTY()
	class AHandToHand_MOVEGameMode* currGameMode;

	UPROPERTY()
	class UHTH_GameInstance* hthGameInstance;

	// 적 생성 함수
	UFUNCTION()
	void CreateEnemy();

	// 스폰할 위치 동적 찾아 할당하기
	UFUNCTION()
	void FindSpawnPoints();
};
