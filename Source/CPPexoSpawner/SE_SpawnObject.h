// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SE_Spawner.h"
#include "SE_SpawnObject.generated.h"

UCLASS()
class CPPEXOSPAWNER_API ASE_SpawnObject : public ASE_Spawner
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> staticMesh = nullptr;
public:	
	// Sets default values for this actor's properties
	ASE_SpawnObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
