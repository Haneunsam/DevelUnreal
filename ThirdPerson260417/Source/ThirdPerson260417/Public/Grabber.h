// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSON260417_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnyWhere)
	float MaxGrabDistance = 400;	// 잡을 수 있는 거리

	UPROPERTY(EditAnyWhere)
	float GrabRadius = 100;		// 잡을 수 있는 크기

	UPROPERTY(EditAnyWhere)
	float HoldDistance = 400;	// 잡고 유지 할 수 있는 거리

public:
	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();


	UPhysicsHandleComponent* GetphysicsHandle() const;
	bool GetGrabableInReach(FHitResult& outHitResult) const;
};
