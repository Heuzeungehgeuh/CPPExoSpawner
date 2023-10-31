// Fill out your copyright notice in the Description page of Project Settings.


#include "SE_Spawner.h"
#include "SE_SpawnObject.h"
// Sets default values
ASE_Spawner::ASE_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASE_Spawner::BeginPlay()
{
	Super::BeginPlay();
    
    Spawn();
                
            
       
   
}

void ASE_Spawner::Spawn()
{
    /*int MaxObjectsToSpawn = 20;
    
    TSubclassOf<AActor> ObjectClassToSpawn = ASE_SpawnObject::StaticClass();*/

    FVector SpawnLocation = GetActorLocation();

    for (int i = 0; i < MaxObjectsToSpawn; ++i)
    {
        if (i >= MaxObjectsToSpawn)
        {
            break;
        }

        ASE_SpawnObject* NewObject = GetWorld()->SpawnActor<ASE_SpawnObject>(actorToSpawn, SpawnLocation, FRotator::ZeroRotator);

        if (!NewObject)return;
        SpawnLocation.Y += 100.0f;
       
       // allActors.Add(NewObject);
    }
}

// Called every frame
void ASE_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

