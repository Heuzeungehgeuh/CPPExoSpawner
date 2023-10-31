// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_SpawnItem.generated.h"

class AS_Spawner;
UCLASS()
class CPPEXOSPAWNER_API AS_SpawnItem : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> staticMesh = nullptr;
	UPROPERTY(EditAnywhere)
		AS_Spawner* spawner = nullptr;
		//UPROPERTY(EditAnywhere)

public:	
	// Sets default values for this actor's properties
	AS_SpawnItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Test();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InitSpawnItem(AS_Spawner* _spawner);

};
