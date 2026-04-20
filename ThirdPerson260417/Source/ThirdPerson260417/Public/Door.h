// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class ATrigger;

UCLASS()
class THIRDPERSON260417_API ADoor : public AActor
{
	GENERATED_BODY()
	
private:
	FVector StartLocation;
	float CurrentOffset = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	ATrigger* Trigger;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;

};
