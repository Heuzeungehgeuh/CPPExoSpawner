// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_GridManager.generated.h"

UCLASS()
class CPPEXOSPAWNER_API AS_GridManager : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventTest);
	UPROPERTY()
		FOnEventTest onEventTest;
public : 
	FOnEventTest& OnEventTest() { return onEventTest; }

public:	
	// Sets default values for this actor's properties
	AS_GridManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	UFUNCTION()
	void Test();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
