// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger.h"

// Sets default values
ATrigger::ATrigger():ButtonState(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}

//엑터와 충돌했을 때
void ATrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// 부모 클래스의 로직을 유지하기 위해 Super 호출(권장)
	Super::NotifyActorBeginOverlap(OtherActor);

	// 충돌한 상대방(OtherActor)이 존재할 때 로직 실행
	if (OtherActor && OtherActor != this) {
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		
		// 겹쳐있는 액터가 1개 이상이면 켜짐
		if (OverlappingActors.Num() > 0) {
			ButtonState = true;
		}
	}
}

//충돌한 엑터와 떨어졌을 때
void ATrigger::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (OtherActor && OtherActor != this) {
		TArray<AActor*> OverlappingActors;
		GetOverlappingActors(OverlappingActors);
		
		// 겹쳐있는 액터가 하나도 없어야 꺼짐
		if (OverlappingActors.Num() == 0) {
			ButtonState = false;
		}
	}
}



