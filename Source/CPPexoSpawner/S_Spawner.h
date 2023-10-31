// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Spawner.generated.h"


class AS_SpawnItem;
UCLASS()
class CPPEXOSPAWNER_API AS_Spawner : public AActor
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerElapsed);
	UPROPERTY()
		FOnTimerElapsed onTimerElapsed;

		//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(EFindFirstObjectOptions, ....)
		//DECLARE_DYNAMIC_MULTICAST_DELEGATE
	/*UPROPERTY()
		FTimerHandle timerSpawn;*/


	UPROPERTY(EditAnywhere, Category="Spawner|Settings")
		TSubclassOf<AS_SpawnItem> actorToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useDecreasingSpawnRate = false;
	UPROPERTY(VisibleAnywhere, Category = "Spawner|Settings|Time")
		float currentTime = 0;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Time")
		float timerSpawnRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useCustomSpawnLocation = false;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		float spawnRateDecreasingValue = -0.1f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		float minSpawnRate = 0.3f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useSpawnCountLimit = false;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		int spawnCountLimit = 10;
	UPROPERTY(VisibleAnywhere, Category = "Spawner|Settings")
		int currentSpawnCount = 0;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|CustomLocation")
		TObjectPtr<USceneComponent>customSpawnLocationGizmo = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|CustomLocation")
		FVector customSpawnLocation = FVector::ZeroVector; // {0, 0, 0 } | FVector(0)
	
		
public:	
	// Sets default values for this actor's properties
	AS_Spawner();

public:
	FVector GetSpawnLocation();
	bool GetIsSpawnAllowed() { return currentSpawnCount < spawnCountLimit; } // peut etre déclaré ici car fonction très simple souvent les Gets et les Sets
	FOnTimerElapsed& OnTimerElapsed() { return onTimerElapsed; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float IncreaseTime(const float& _currentTime, const float& _maxTime);
	void DebugSpawnLocation(const FVector& _location);
	void Debug();
	void AddSpawnRate(const float& _toAdd);
	void AddSpawnCount(const int& _toAdd);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Spawn();
	void SetCurrentTime(const float& _value);
};
