// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingBox.h"

// Sets default values
AMovingBox::AMovingBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingBox::BeginPlay()
{

	Super::BeginPlay();

	/*UE_LOG(LogTemp, Display, TEXT("This is Display"));
	UE_LOG(LogTemp, Warning, TEXT("This is Warnig"));
	UE_LOG(LogTemp, Error, TEXT("This is Error"));*/
	//UE_LOG(LogTemp, Error, TEXT("%s_Name : %f", *GetName(), 0.5f));

	StartLocation = GetActorLocation();
}

void AMovingBox::RotateBox(float Deltatime)
{
	AddActorLocalRotation(RotationVelocity * Deltatime);
}

void AMovingBox::MoveBox(float Deltatime)
{
	// 시간 누적
	RunningTime += Deltatime;
	
	// 2. 사인 함수를 이용한 변위 계산(DEltaLocation)
	// -1.0 ~ 1.0 사이를 반복하는 사인값에 Distance를 곱합
	float SineValue = FMath::Sin(RunningTime * Speed);
	float DeltaMovement = SineValue * Distance;

	// 방향 설정 (엑터의 오른쪽 방향 벡터를 활용)
	//FVector Direction = GetActorRightVector();

	// 4. 새로운 위치 계산 및 설정
	// 기준 위치 + (오른쪽 방향 * 이동 거리)
	//FVector NewLocation = StartLocation + (Direction * DeltaMovement);
	
	FVector NewLocation = { StartLocation.X , StartLocation.Y + DeltaMovement, StartLocation.Z };

	SetActorLocation(NewLocation);
}

// Called every frame
void AMovingBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateBox(DeltaTime);
	MoveBox(DeltaTime);


}

