// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ES_Eater.generated.h"



// il doit trouver tous les actors docn faire un tableau d'actor // OK
//une fois a distance assez proche il le fait disparaitre // OK
//rendre invisible: SetActorHiddenInGame(true); //rend les collision OFF: SetActorEnableCollision(false); // OK 
// 
//il doit se diriger vers un des actor du tableau de façon aléatoire
//il doit ensuite se rendre a une nouvelle position on est donc dans une boucle for, la fin de la boucle et le nombre d'acteur quand le tableau arrive a 0
//si possible scale +0.1 a chaque actor disparue





UCLASS()
class CPPEXOSPAWNER_API AES_Eater : public AActor
{
	GENERATED_BODY()
#pragma region UPROPRETY Timer
		UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float currentTime = 0;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float timerSpawnRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float spawnRateDecreasingValue = -0.1f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings|Timer")
		float minSpawnRate = 0.3f;
	UPROPERTY(EditAnywhere, Category = "Spawner|Settings")
		bool useDecreasingSpawnRate = false;
#pragma endregion
	UPROPERTY(EditAnywhere, Category = "Settings|Body")
		TObjectPtr<UStaticMeshComponent> staticMesh = nullptr;
	UPROPERTY(EditAnywhere)
		float minDistanceAllowed = 150.f;
	UPROPERTY(EditAnywhere)
		float alpha = 2;
	
	UPROPERTY(EditAnywhere)
		TArray<AActor*> allActors;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actorToFind = nullptr;
public:	
	// Sets default values for this actor's properties
	AES_Eater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:

	void FindGameItems();

	void PlayerGameLoop();

	void PlayerDetectionBehaviour(AActor* _target);
	void ChooseTarget();
	void ChangeColor(AActor* _target);
	void LerpProgress(const FVector& _locationToRush);
	
	void EnlargeYourCube();

	float IncreaseTime(const float& _currentTime, const float& _maxTime);
	void AddSpawnRate(const float& _toAdd);


};
