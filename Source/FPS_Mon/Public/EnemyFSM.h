// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// ����� ���¸� ����
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_MON_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	UPROPERTY(EditAnywhere, Category=FSM, BlueprintReadWrite)
	EEnemyState m_state;

	// �ʿ�Ӽ� : ��ٸ��ð�, ����ð�
	UPROPERTY(EditAnywhere, Category=FSM)
	float idleDelayTime = 2;

	UPROPERTY()
	float currentTime = 0;

	// �ʿ�Ӽ� : Ÿ��, �̵��ӵ�(Character Movement �� �ִ� �Ӽ��� ���)
	UPROPERTY(EditAnywhere, Category=Target)
	class AFPSPlayer* target;

	UPROPERTY()
	class AEnemy* me;

	// �ʿ�Ӽ� : ���ݹ���
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 200;

	// �ʿ�Ӽ� : ���ݴ��ð�
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackDelayTime = 2;

	// �ʿ�Ӽ� : �ǰݴ��ð�
	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2;

	// hp
	UPROPERTY(EditAnywhere, Category = FSM)
	int hp = 3;

	// Damage ���� �� �ڷ� �и� ��
	UPROPERTY(EditAnywhere, Category = FSM)
	float knockback = 500;

	// Damage ���� �� �˹� ���� ����
	UPROPERTY()
	FVector knockbackPos;

	// Enemy �� ����ϰ� �ִ� AIController ���
	UPROPERTY()
	class AAIController* ai;

	// Enemy �� ����ϰ� �ִ� Animation Instance ���
	UPROPERTY()
	class UEnemyAnimInstance* anim;

	// �������� ��ã�� �� ������
	UPROPERTY()
	FVector randomPos;

	UPROPERTY(EditAnywhere, Category=AI)
	class AActor* aiDebugActor;

	// ����� NavigationSystem ��ü ���
	UPROPERTY()
	class UNavigationSystemV1* ns;

private:
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

	// �Ķ���ͷ� ���ϴ� ���͸� ������ �� ���͸� �������� ������ġ �˷��ִ� �Լ�
	bool GetTargetLocation(const AActor* targetActor, float radius, FVector &dest);

public:
	// �ǰ� �޾��� �� ó���� �Լ�
	void OnDamageProcess(FVector shootDirection);
};
