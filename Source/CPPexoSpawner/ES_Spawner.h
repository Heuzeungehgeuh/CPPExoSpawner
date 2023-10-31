// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ES_Spawner.generated.h"


class AES_SpawnItem;

UCLASS()
class CPPEXOSPAWNER_API AES_Spawner : public AActor
{
	GENERATED_BODY()

#pragma region Declaration DELEGATE

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerElapsed, const FVector&, _spawnLocation); //Rajouter un param avec la position
	UPROPERTY()
		FOnTimerElapsed onTimerElapsed;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnCount, int, _toAdd);
	UPROPERTY()
		FOnSpawnCount onSpawnCount;
#pragma endregion

#pragma region UPROPERTY Settings
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		TSubclassOf<AES_SpawnItem> actorToSpawn = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useCustomSpawnLocation = false;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useDecreasingSpawnRate = false;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		int maxSpawnChoose = 10;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Grille")
		int line = 10;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Grille")
		int colonne = 10;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Grille")
		float interX = 100;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Grille")
		float interY = 100;
		//int line, int Colonne, float x, float y
#pragma endregion
#pragma region UPROPRETY Timer
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float currentTime = 0;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float timerSpawnRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float spawnRateDecreasingValue = -0.1f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float minSpawnRate = 0.3f;
#pragma endregion
#pragma region UPROPERTY MouseSettings
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Mouse")
		FVector MouseLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Mouse")
		FVector MouseDirection = FVector::ZeroVector;
#pragma endregion
#pragma region UPROPERTY Other
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|CustomLocation")
		FVector customSpawnLocation = FVector::ZeroVector; // {0, 0, 0 } | FVector(0)
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Body")
		TObjectPtr<UStaticMeshComponent> staticMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Table")
		TArray<AActor*> allActors;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Table")
		TSubclassOf<AActor> actorToFind = nullptr;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Table")
		int spawnItem = 0;
#pragma endregion

public:	
	// Sets default values for this actor's properties
	AES_Spawner();


#pragma region Fonction Protected
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnMouseClick();
	void DebugSpawnLocation(const FVector& _location);
	void Debug();
	float IncreaseTime(const float& _currentTime, const float& _maxTime);
	void AddSpawnRate(const float& _toAdd);
	//void CustomTickRate(const float& _currentTime, timerTickRate);
#pragma endregion

#pragma region Fonction Public
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Grille(int Lines, int Colonnes, float x, float y);
#pragma region Fonction DELEGATE
public:
	UFUNCTION()
	void GetCountSpawn(int _toAdd) 
	{ 
		//if (!spawnItem)return;
		spawnItem += _toAdd;
		//_toAdd = spawnItem;
		UE_LOG(LogTemp, Warning, TEXT("%i"), spawnItem); 

	}
	UFUNCTION()
	void SpawnGrille(const FVector& _localSpawn);

#pragma endregion

	void Spawn();
	void FindGameItems();
	void PlayerGameLoop();

	FOnTimerElapsed& OnTimerElapsed() { return onTimerElapsed; }
	FOnSpawnCount& OnSpawnCount() { return onSpawnCount; }

#pragma endregion

};

