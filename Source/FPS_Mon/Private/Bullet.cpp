// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌체 등록하고 
	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	// 루트로 설정
	RootComponent = collision;	
	collision->SetCollisionProfileName(TEXT("BlockAll"));

	// 외관
	bodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	bodyMesh->SetupAttachment(collision);
	// 충돌설정
	bodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 발사체 컴포넌트
	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	// movement 가 갱신시킬 컴포넌트 지정
	movement->SetUpdatedComponent(collision);
	// movement 컴포넌트의 초기값을 설정
	// 튕길지여부
	movement->bShouldBounce = true;
	movement->Bounciness = 0.3f;
	// 속도
	movement->MaxSpeed = 5000;
	movement->InitialSpeed = 5000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

