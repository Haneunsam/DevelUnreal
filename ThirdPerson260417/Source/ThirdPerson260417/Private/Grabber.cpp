// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetphysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetphysicsHandle();
	if (PhysicsHandle == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber: PhysicsHandleComponent missing!"));
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabableInReach(HitResult);

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();	// 내가 잡은 물체
		AActor* HitActor = HitResult.GetActor();

		if (HitComponent != nullptr && HitActor != nullptr)
		{
			HitComponent->SetSimulatePhysics(true);	// 물리 시뮬레이션을 켜야 PhysicsHandle로 사용 가능
			HitComponent->WakeAllRigidBodies(); // 물체가 안 움직일 때는 최적화를 위해 잠금하는 기능이 있는데 그걸 해제
			HitActor->Tags.Add("Grabbed"); //해당 엑터의 태그 그랩 추가

			// 만약 기존에 엑터가 자식으로 있으면 월드 공간으로 빼는데 transfrom 유지
			HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

			PhysicsHandle->GrabComponentAtLocationWithRotation(
				HitComponent, // 맞은 컴포넌트
				NAME_None,	// 본 이름, 본 없음
				HitResult.ImpactPoint, // 충돌 지점
				GetComponentRotation());
		}
	}
}

void UGrabber::Release() 
{
	UPhysicsHandleComponent* PhysicsHandle = GetphysicsHandle();
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent();
	}
}


UPhysicsHandleComponent* UGrabber::GetphysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Equires a UPhysicsHandleComponent"));
	}
	
	return Result;
}

bool UGrabber::GetGrabableInReach(FHitResult& outHitResult) const
{
	FVector Start = GetComponentLocation(); // 시작점
	FVector End = Start + GetForwardVector() * MaxGrabDistance; // 끝점

	// 화면에 디버그용 선이랑 Sphere 출력
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5);
	DrawDebugSphere(GetWorld(), End, GrabRadius, 10, FColor::Blue , false, 5);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	return GetWorld()->SweepSingleByChannel(
		outHitResult,	//맞은애
		Start, End,	//위치
		FQuat::Identity,	
		ECC_GameTraceChannel1, // 채널 설명
		Sphere,	//충돌 모양
		TraceParams); //무시할 대상
}
