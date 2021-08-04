// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "FPSPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "Enemy.h"
#include <DrawDebugHelpers.h>
#include "FPS_Mon.h"
#include <AIController.h>
#include "EnemyAnimInstance.h"

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

	// AIController �Ҵ�
	ai = Cast<AAIController>(me->GetController());

	anim = Cast<UEnemyAnimInstance>(me->GetMesh()->GetAnimInstance());

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

		// 4. Animation �� ���µ� Move �� �ٲ��ְ� �ʹ�.
		anim->isMoving = true;
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
	
	// AI�� ��ã�� ����� �̿��ؼ� �̵��ϰ� �ʹ�.
	if (ai)
	{
		ai->MoveToActor(target);
	}

	//me->AddMovementInput(direction, 1);
		
	// �̵��ϴ� �������� ȸ���ϰ� �ʹ�.
	//me->GetCharacterMovement()->bOrientRotationToMovement = true;

	// Ÿ�ٹ���
	FRotator targetRot = direction.ToOrientationRotator();
	FRotator myRot = me->GetActorRotation();

	// �ε巴�� ȸ���ϰ� �ʹ�.
	myRot = FMath::Lerp(myRot, targetRot, 5 * GetWorld()->DeltaTimeSeconds);

	//me->SetActorRotation(myRot);

	// ���ݹ����� �ð������� ǥ���غ���
	DrawDebugSphere(GetWorld(), me->GetActorLocation(), attackRange, 10, FColor::Red);

	// 2. Ÿ�ٰ��� �Ÿ��� ���ݹ����ȿ� ������ ���¸� �������� �ٲٰ� �ʹ�.
	if (distance < attackRange)
	{
		m_state = EEnemyState::Attack;
		currentTime = attackDelayTime;
	}

		// P = P0 + vt
	/*FVector P0 = me->GetActorLocation();
	FVector p = P0 + direction * 500 * GetWorld()->DeltaTimeSeconds;

	me->SetActorLocation(p, true);*/
}

// �����ð��� �ѹ��� �����ϰ� �ʹ�.
// �ʿ�Ӽ� : ���ݴ��ð�
void UEnemyFSM::AttackState()
{
	// �����ð��� �ѹ��� �����ϰ� �ʹ�.	
	// 1. �ð��� �귶���ϱ�
	currentTime += GetWorld()->DeltaTimeSeconds;
	// 2. ���ݽð��� �����ϱ�
	if(currentTime > attackDelayTime)
	{
		// 3. ������ �ֿܼ� ���
		PRINTLOG(TEXT("Attack!!!"));
		currentTime = 0;
	}

	// Ÿ���� �������� ���󰡰� �ʹ�.
	// Ÿ�ٰ��� �Ÿ�
	//FVector direction = target->GetActorLocation() - me->GetActorLocation();
	// �ѻ����� �Ÿ�
	float distance = FVector::Dist(target->GetActorLocation(), me->GetActorLocation());
	// -> ���¸� Move �� ��ȯ�ϰ� �ʹ�.
	// -> Ÿ�ٰ��� �Ÿ��� ���ݹ����� �����
	if (distance > attackRange)
	{
		m_state = EEnemyState::Move;
	}
}

// �����ð��� ������ ���¸� Idle �� �ٲٰ� �ʹ�.
// �ʿ�Ӽ� : �ǰݴ��ð�
// -> �˹��� ������ Idle �� ���¸� �ٲ���.
void UEnemyFSM::DamageState()
{
	// Lerp �� �̿��Ͽ� knock back ����
	FVector myPos = me->GetActorLocation();

	myPos = FMath::Lerp(myPos, knockbackPos, 20 * GetWorld()->DeltaTimeSeconds);

	float distance = FVector::Dist(myPos, knockbackPos);
	// ���� ��ġ�� ������ �Ÿ��� ���� ������ �����Ѱ����� �Ǵ�����
	if (distance < 21.0f)
	{
		myPos = knockbackPos;
		m_state = EEnemyState::Idle;
		currentTime = 0;
	}

	me->SetActorLocation(myPos);
}

void UEnemyFSM::DieState()
{
}

// �ǰ� �޾��� �� ó���� �Լ�
// �ǰ� �޾��� �� hp �� ���ҽ�Ű�� 0 ���ϸ� ���¸� Die �� �ٲٰ� ���ֹ�����
void UEnemyFSM::OnDamageProcess(FVector shootDirection)
{
	hp--;
	if (hp <= 0)
	{
		m_state = EEnemyState::Die;
		me->Destroy();
		return;
	}
	
	// ������ �ڷ� �и����� ó���ϰ� �ʹ�.
	// �и� ������ �ʿ�
	//me->SetActorLocation(me->GetActorLocation() + shootDirection * knockback);
	knockbackPos = me->GetActorLocation() + shootDirection * knockback;

	// ���¸� Damage �� �ٲٰ� �ʹ�.
	m_state = EEnemyState::Damage;

	// �˶�������� �ð��� �ٵǸ� ���¸� Idle �� �ٲٰ� �ʹ�.
	FTimerHandle damageTimer;

	//GetWorld()->GetTimerManager().SetTimer(damageTimer, this, &UEnemyFSM::DamageState, damageDelayTime, false);
}

