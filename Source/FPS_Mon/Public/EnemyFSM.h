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

private:
	void IdleState();
	void MoveState();
	void AttackState();
	void DamageState();
	void DieState();
};
