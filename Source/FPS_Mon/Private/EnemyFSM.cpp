// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "FPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "Enemy.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	// 내 액터찾기
	me = Cast<AEnemy>(GetOwner());

	// 	   -> 에디터에서 할당해주기
	// 	   -> 동적으로 타겟을 찾아야 할 필요
	target = Cast<AFPSPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AFPSPlayer::StaticClass()));

	/*TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFPSPlayer::StaticClass(), actors);*/

	/*for (int i=0;i<actors.Num();i++)
	{
		AActor* t = actors[i];
		target = Cast<AFPSPlayer>(t);

	}*/

	/*for (auto t : actors)
	{
		target = Cast<AFPSPlayer>(t);
		break;
	}*/

	/*for (TActorIterator<AFPSPlayer> it(GetWorld()); it; ++it)
	{
		target = *it;
	}*/
	
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 목차(뼈대)를 작성
	switch (m_state)
	{
	case EEnemyState::Idle:
		IdleState();
		break;
	case EEnemyState::Move:
		MoveState();
		break;
	case EEnemyState::Attack:
		AttackState();
		break;
	case EEnemyState::Damage:
		DamageState();
		break;
	case EEnemyState::Die:
		DieState();
		break;
	}
}

// 일정시간동안 기다리다가 상태를 Move 로 바꿔주자.
// 필요속성 : 기다릴시간, 경과시간
void UEnemyFSM::IdleState()
{
	// 일정시간동안 기다리다가 상태를 Move 로 바꿔주자.
	// 1. 시간이 흘렀으니까
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. 대기시간이 다됐으니까
	if(currentTime > idleDelayTime)
	{
		// 3. 상태를 Move 로 바꿔주자.
		m_state = EEnemyState::Move;
		currentTime = 0;
	}
}

// 타겟 방향으로 이동하고 싶다.
// 필요속성 : 타겟, 이동속도
void UEnemyFSM::MoveState()
{
	// 타겟 방향으로 이동하고 싶다.
	// 1. 타겟이 있어야한다.
	

	// 2. 방향이필요
	// 	   direction = target - me (위치)
	FVector direction = target->GetActorLocation() - me->GetActorLocation();
	direction.Normalize();
	// 3. 이동하고싶다.
	
	me->AddMovementInput(direction, 1);
		// P = P0 + vt
	/*FVector P0 = me->GetActorLocation();
	FVector p = P0 + direction * 500 * GetWorld()->DeltaTimeSeconds;

	me->SetActorLocation(p, true);*/
}

void UEnemyFSM::AttackState()
{
}

void UEnemyFSM::DamageState()
{
}

void UEnemyFSM::DieState()
{
}

