// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);		//(float DeltaSeconds) <- 함수 실행시에는 자료형을 쓰지않는다.

	//플레이어이 이동 속도를 가져와 speed 에 할당하고 싶다
	//1. 소유 폰 얻어오기
	APawn* ownerPawn = TryGetPawnOwner();		//함수에 마우스대면 APawn*
	//2. 플레이어로 캐스팅하기
	//auto player = Cast<>(ownerPawn);
}