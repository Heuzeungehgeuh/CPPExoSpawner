// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SE_Spawner.generated.h"
class ASE_SpawnObject;
UCLASS()
class CPPEXOSPAWNER_API ASE_Spawner : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		int MaxObjectsToSpawn = 20;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ASE_SpawnObject> actorToSpawn = nullptr;
	//TSubclassOf<AActor> ObjectClassToSpawn = ASE_SpawnObject::StaticClass();

public:	
	// Sets default values for this actor's properties
	ASE_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
