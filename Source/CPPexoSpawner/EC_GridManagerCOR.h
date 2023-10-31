// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EC_GridManagerCOR.generated.h"

UCLASS()
class CPPEXOSPAWNER_API AEC_GridManagerCOR : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEC_GridManagerCOR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
