// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class HANDTOHAND_MOVE_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// ���¸ӽ� ��� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	EEnemyState animState;

	// ���� ���� ������� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bAttackPlay = false;

	// ���� ���� ������� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bAttackPlay1 = false;

	// ���� ���� ������� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bAttackPlay2 = false;
	
	// ���� �ִϸ��̼� ������ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
	void OnStartAttackAnimation();

	// �ǰ� �ִϸ��̼� ��� �Լ�
	UFUNCTION(BlueprintImplementableEvent, Category=FSMEvent)
	void PlayDamageAnim(FName sectionName);

	// ���� ���� �ִϸ��̼� ���� ����
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=FSM)
	bool bDieDone = false;

	// Move(Run) ���� ������� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FSM)
	bool bRunPlay = false;	
};
