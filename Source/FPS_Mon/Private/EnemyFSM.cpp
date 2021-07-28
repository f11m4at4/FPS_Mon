// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "FPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "Enemy.h"
#include <DrawDebugHelpers.h>

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

	// �� ����ã��
	me = Cast<AEnemy>(GetOwner());

	// 	   -> �����Ϳ��� �Ҵ����ֱ�
	// 	   -> �������� Ÿ���� ã�ƾ� �� �ʿ�
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

	// ����(����)�� �ۼ�
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

// �����ð����� ��ٸ��ٰ� ���¸� Move �� �ٲ�����.
// �ʿ�Ӽ� : ��ٸ��ð�, ����ð�
void UEnemyFSM::IdleState()
{
	// �����ð����� ��ٸ��ٰ� ���¸� Move �� �ٲ�����.
	// 1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. ���ð��� �ٵ����ϱ�
	if(currentTime > idleDelayTime)
	{
		// 3. ���¸� Move �� �ٲ�����.
		m_state = EEnemyState::Move;
		currentTime = 0;
	}
}

// 1. Ÿ�� �������� �̵��ϰ� �ʹ�.
// �ʿ�Ӽ� : Ÿ��, �̵��ӵ�
// 2. Ÿ�ٰ��� �Ÿ��� ���ݹ����ȿ� ������ ���¸� �������� �ٲٰ� �ʹ�.
// �ʿ�Ӽ� : ���ݹ���
void UEnemyFSM::MoveState()
{
	// Ÿ�� �������� �̵��ϰ� �ʹ�.
	// 1. Ÿ���� �־���Ѵ�.
	

	// 2. �������ʿ�
	// 	   direction = target - me (��ġ)
	FVector direction = target->GetActorLocation() - me->GetActorLocation();
	// �ѻ����� �Ÿ�
	float distance = direction.Size();

	direction.Normalize();
	// 3. �̵��ϰ�ʹ�.
	
	me->AddMovementInput(direction, 1);

	// �̵��ϴ� �������� ȸ���ϰ� �ʹ�.
	//me->GetCharacterMovement()->bOrientRotationToMovement = true;

	// Ÿ�ٹ���
	FRotator targetRot = direction.ToOrientationRotator();
	FRotator myRot = me->GetActorRotation();

	// �ε巴�� ȸ���ϰ� �ʹ�.
	myRot = FMath::Lerp(myRot, targetRot, 5 * GetWorld()->DeltaTimeSeconds);

	me->SetActorRotation(myRot);

	// ���ݹ����� �ð������� ǥ���غ���
	DrawDebugSphere(GetWorld(), me->GetActorLocation(), attackRange, 1, FColor::Red);

	// 2. Ÿ�ٰ��� �Ÿ��� ���ݹ����ȿ� ������ ���¸� �������� �ٲٰ� �ʹ�.
	if (distance < attackRange)
	{
		m_state = EEnemyState::Attack;
	}

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

