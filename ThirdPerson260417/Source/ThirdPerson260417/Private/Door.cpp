// Fill out your copyright notice in the Description page of Project Settings.

#include "Trigger.h"
#include "Door.h"
#include "Engine/Engine.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

    if (Trigger == nullptr) {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Warning: No trigger specified."));
    }

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (Trigger == nullptr)
    {
        return;
    }

    bool bIsPressed = Trigger->GetButtonState();
    float Speed = 1.0f; // 내려가는 속도
    float MaxDistance = 500.0f;
    // 트리거 상태에 따라 CurrentOffset을 0~1 사이로 부드럽게 변화시킴
    if (bIsPressed)
    {
        CurrentOffset = FMath::FInterpTo(CurrentOffset, 1.0f, DeltaTime, Speed);
    }
    else
    {
        CurrentOffset = FMath::FInterpTo(CurrentOffset, 0.0f, DeltaTime, Speed);
    }
    // 시작 위치에서 Offset만큼 반영된 위치로 이동
    FVector NewLocation = StartLocation;
    NewLocation.Z -= (CurrentOffset * MaxDistance);
    SetActorLocation(NewLocation);
}