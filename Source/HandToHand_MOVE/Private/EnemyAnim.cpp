// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "EnemyFSM.h"
#include "Enemy.h"

void UEnemyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
	bAttackPlay1 = false;
	bAttackPlay2 = false;
}
	