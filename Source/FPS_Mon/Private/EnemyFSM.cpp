// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

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

	// ...
	
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

void UEnemyFSM::MoveState()
{
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

