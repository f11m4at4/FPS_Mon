// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include "FPSPlayer.h"
#include <Components/ArrowComponent.h>
#include "Bullet.h"

// Sets default values for this component's properties
UPlayerFire::UPlayerFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


// Called when the game starts
void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UPlayerFire::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<AFPSPlayer>(GetOwner());
	// player �� �ִ� OnInputDelegate �� ó�� �Լ��� ����ϰ� �ʹ�.
	me->OnInputDelegate.AddUObject(this, &UPlayerFire::SetupPlayerInputComponent);

	// �ѱ� ������Ʈ ��������
	firePosition = Cast<UArrowComponent>(me->GetDefaultSubobjectByName(TEXT("FirePosition")));
}

// Called every frame
void UPlayerFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerFire::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &UPlayerFire::Fire);
}

// ����ڰ� �߻��ư�� ������ �Ѿ��� �߻��ϰ� �ʹ�.
void UPlayerFire::Fire()
{
	GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());
}

