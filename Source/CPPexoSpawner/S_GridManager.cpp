// Fill out your copyright notice in the Description page of Project Settings.


#include "S_GridManager.h"
#include "EC_GridItem.h"
// Sets default values
AS_GridManager::AS_GridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AS_GridManager::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Test"))
}

// Called when the game starts or when spawned
void AS_GridManager::BeginPlay()
{
	Super::BeginPlay();
	onEventTest.AddDynamic(this, &AS_GridManager::Test);
	AEC_GridItem* _spawnedItem = GetWorld()->SpawnActor<AEC_GridItem>();
	if (!_spawnedItem)return;
	_spawnedItem->SetGrid(this);
	onEventTest.Broadcast();
	
}

// Called every frame
void AS_GridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

