// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBox.generated.h"

UCLASS()
class THIRDPERSON260417_API AMovingBox : public AActor
{
	GENERATED_BODY()
private:
	FVector StartLocation; // 기준 위치
	float RunningTime = 0.0f;	// 누적 시간
public:
	//UPROPERTY언리얼 에디터에서 해당 변수를 제어 하도록 만들어주는 매크로
	UPROPERTY(EditAnyWhere, Category = "Movement")
	FRotator RotationVelocity = FRotator(0, 0, 0);
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float Speed = 2.0f;	
	UPROPERTY(EditAnyWhere, Category = "Movement")
	float Distance = 500.0f;
public:	
	// Sets default values for this actor's properties
	AMovingBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void RotateBox(float Deltatime);
	void MoveBox(float Deltatime);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
