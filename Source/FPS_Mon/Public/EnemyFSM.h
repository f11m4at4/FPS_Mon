// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"

// 사용할 상태를 정의
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

	// 필요속성 : 기다릴시간, 경과시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float idleDelayTime = 2;

	UPROPERTY()
	float currentTime = 0;

	// 필요속성 : 타겟, 이동속도(Character Movement 에 있는 속성을 사용)
	UPROPERTY(EditAnywhere, Category=Target)
	class AFPSPlayer* target;

	UPROPERTY()
	class AEnemy* me;

	// 필요속성 : 공격범위
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 200;

	// 필요속성 : 공격대기시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackDelayTime = 2;

	// 필요속성 : 피격대기시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 2;

	// hp
	UPROPERTY(EditAnywhere, Category = FSM)
	int hp = 3;

	// Damage 받을 때 뒤로 밀릴 힘
	UPROPERTY(EditAnywhere, Category = FSM)
	float knockback = 500;

	// Damage 받을 때 넉백 종료 지점
	UPROPERTY()
	FVector knockbackPos;

	// Enemy 가 사용하고 있는 AIController 기억
	UPROPERTY()
	class AAIController* ai;

private:
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();

public:
	// 피격 받았을 때 처리할 함수
	void OnDamageProcess(FVector shootDirection);
};
