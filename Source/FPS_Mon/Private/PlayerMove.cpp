// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "FPSPlayer.h"
#include "FPS_Mon.h"

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
}


// Called when the game starts
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	
}


void UPlayerMove::InitializeComponent()
{
	Super::InitializeComponent();

	me = Cast<AFPSPlayer>(GetOwner());
	// player 에 있는 OnInputDelegate 에 처리 함수를 등록하고 싶다.
	me->OnInputDelegate.AddUObject(this, &UPlayerMove::SetupPlayerInputComponent);
}

// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerMove::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// 사용자의 입력을 처리할 함수 Bind
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &UPlayerMove::Vertical);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &UPlayerMove::Horizontal);
}

void UPlayerMove::Horizontal(float value)
{
	FVector dir = me->GetControlRotation().Quaternion().GetRightVector();

	me->AddMovementInput(dir, value);
}

void UPlayerMove::Vertical(float value)
{
	// 방향
	// 컨트롤러에 의해서 방향이 좌우된다.
	//FVector dir = FRotationMatrix(me->GetControlRotation()).GetScaledAxis(EAxis::X);
	//FVector dir = FTransform(me->GetControlRotation()).GetRotation().GetForwardVector();
	FVector dir = me->GetControlRotation().Quaternion().GetForwardVector();

	me->AddMovementInput(dir, value);
}

