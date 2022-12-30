// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("SkeletalMesh'/Game/KDH/Enemy/Resource/Ch18_nonPBR.Ch18_nonPBR'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}

	// EnemyFSM 컴포넌트 추가
	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));
	
	// 애니메이션 블루프린트 할당하기
	ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("AnimBlueprint'/Game/KDH/Enemy/Bluprints/ABP_Enemy.ABP_Enemy_C'"));
	if (tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}

	// 월드에 배치되거나 스폰될 때 자동으로
	// AIController 부터 Process 될 수 있도록 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 왼쪽 주먹 충돌 박스 생성
	LeftFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFistCollisionBox"));
	LeftFistCollisionBox->SetupAttachment(RootComponent);
	LeftFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);
	LeftFistCollisionBox->SetRelativeScale3D(FVector(0.1875));
	// 인게임에서 충돌 박스 보이게 하기
	LeftFistCollisionBox->SetHiddenInGame(false);

	// 오른쪽 주먹 충돌 박스 생성
	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox"));
	RightFistCollisionBox->SetupAttachment(RootComponent);
	RightFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
	RightFistCollisionBox->SetRelativeScale3D(FVector(0.1875));

	// 인게임에서 충돌 박스 보이게 하기
	RightFistCollisionBox->SetHiddenInGame(false);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();		

	// UEnemyAnim* 할당
	anim = Cast<UEnemyAnim>(GetMesh()->GetAnimInstance());

	// maxWalkSpeed 값 세팅
	GetCharacterMovement()->MaxWalkSpeed = 100;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	LeftFistCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "fist_l_collision");
	RightFistCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "fist_r_collision");
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 달릴 때 MaxWalkSpeed 설정
	if (anim->bRunPlay == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

