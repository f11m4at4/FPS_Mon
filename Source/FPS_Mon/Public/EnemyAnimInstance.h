// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_MON_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category=FSM, BlueprintReadOnly)
	bool isMoving = false;

	UPROPERTY(EditAnywhere, Category = FSM, BlueprintReadOnly)
	bool isPatrol = false;
};
