// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyManager.h"
#include <Sound/SoundBase.h>
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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
	LeftFistCollisionBox->SetRelativeScale3D(FVector(0.2));
	// 인게임에서 충돌 박스 보이게 하기
	LeftFistCollisionBox->SetHiddenInGame(false);

	// 오른쪽 주먹 충돌 박스 생성
	RightFistCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFistCollisionBox"));
	RightFistCollisionBox->SetupAttachment(RootComponent);
	RightFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);
	RightFistCollisionBox->SetRelativeScale3D(FVector(0.2));
	// 인게임에서 충돌 박스 보이게 하기
	RightFistCollisionBox->SetHiddenInGame(false);

	// 왼쪽 발 충돌 박스 생성
	LeftFootCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFootCollisionBox"));
	LeftFootCollisionBox->SetupAttachment(RootComponent);
	LeftFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	LeftFootCollisionBox->SetNotifyRigidBodyCollision(false);
	LeftFootCollisionBox->SetRelativeScale3D(FVector(0.1875));
	// 인게임에서 충돌 박스 보이게 하기
	LeftFootCollisionBox->SetHiddenInGame(false);

	// 오른쪽 발 충돌 박스 생성
	RightFootCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFootCollisionBox"));
	RightFootCollisionBox->SetupAttachment(RootComponent);
	RightFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	RightFootCollisionBox->SetNotifyRigidBodyCollision(false);
	RightFootCollisionBox->SetRelativeScale3D(FVector(0.1875));
	// 인게임에서 충돌 박스 보이게 하기
	RightFootCollisionBox->SetHiddenInGame(false);

	static ConstructorHelpers::FObjectFinder<USoundBase> tempHitSound(TEXT("SoundWave'/Game/KDH/Enemy/Sound/fist-punch-or-kick-7171.fist-punch-or-kick-7171'"));
	if (tempHitSound.Succeeded())
	{
		hitSound = tempHitSound.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempDeathSound(TEXT("SoundWave'/Game/KDH/Enemy/Sound/death-49098.death-49098'"));
	if (tempDeathSound.Succeeded())
	{
		deathSound = tempDeathSound.Object;
	}

	ConstructorHelpers::FClassFinder<AActor> tempBlood(TEXT("Blueprint'/Game/KDH/Enemy/Effect/BP_Blood_Drops.BP_Blood_Drops_C'"));
	if (tempBlood.Succeeded())
	{
		bloodFactory = tempBlood.Class;
	}
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
	LeftFootCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "LeftFootSocket");
	RightFootCollisionBox->AttachToComponent(GetMesh(), AttachmentRules, "RightFootSocket");

	AActor* eM = UGameplayStatics::GetActorOfClass(GetWorld(), AEnemyManager::StaticClass());
	enemyManager = Cast<AEnemyManager>(eM);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AEnemy::AttackStart()
{
	LeftFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Enabled);
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(true);

	RightFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Enabled);
	RightFistCollisionBox->SetNotifyRigidBodyCollision(true);

	LeftFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Enabled);
	LeftFootCollisionBox->SetNotifyRigidBodyCollision(true);

	RightFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Enabled);
	RightFootCollisionBox->SetNotifyRigidBodyCollision(true);
}
void AEnemy::AttackEnd()
{
	LeftFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	LeftFistCollisionBox->SetNotifyRigidBodyCollision(false);

	RightFistCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	RightFistCollisionBox->SetNotifyRigidBodyCollision(false);

	LeftFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	LeftFootCollisionBox->SetNotifyRigidBodyCollision(false);

	RightFootCollisionBox->SetCollisionProfileName(MeleeCollisionProfile.Disabled);
	RightFootCollisionBox->SetNotifyRigidBodyCollision(false);
}

