// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFire.generated.h"

// ����ڰ� �߻��ư�� ������ �Ѿ��� �߻��ϰ� �ʹ�.
// �ʿ�Ӽ� : �Ѿ˰���
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_MON_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	void Fire();

public:
	// �ʿ�Ӽ� : �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category=BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	// �ʿ�Ӽ�:��������
	UPROPERTY()
	class AFPSPlayer* me;

	UPROPERTY()
	class UArrowComponent* firePosition;

	UPROPERTY(EditAnywhere, Category=FireDistance)
	float fireDistance = 1000;

	UPROPERTY(EditDefaultsOnly, Category=BulletEffect)
	class UParticleSystem* bulletEffect;

	// ���� ���� �� �ε��� ��ü�� ���� ��
	UPROPERTY(EditDefaultsOnly, Category = BulletPower)
	float bulletPower = 100;
};
