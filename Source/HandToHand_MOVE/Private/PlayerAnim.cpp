// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);		//(float DeltaSeconds) <- �Լ� ����ÿ��� �ڷ����� �����ʴ´�.

	//�÷��̾��� �̵� �ӵ��� ������ speed �� �Ҵ��ϰ� �ʹ�
	//1. ���� �� ������
	APawn* ownerPawn = TryGetPawnOwner();		//�Լ��� ���콺��� APawn*
	//2. �÷��̾�� ĳ�����ϱ�
	//auto player = Cast<>(ownerPawn);
}