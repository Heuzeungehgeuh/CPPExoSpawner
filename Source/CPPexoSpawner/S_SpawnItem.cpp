// Fill out your copyright notice in the Description page of Project Settings.


#include "S_SpawnItem.h"
#include "S_Spawner.h"

// Sets default values
AS_SpawnItem::AS_SpawnItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	staticMesh->SetupAttachment(RootComponent);

}



// Called when the game starts or when spawned
void AS_SpawnItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AS_SpawnItem::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}

void AS_SpawnItem::InitSpawnItem(AS_Spawner* _spawner)
{
	if (!_spawner)return;
	spawner = _spawner;
	spawner->OnTimerElapsed().AddDynamic (this, &AS_SpawnItem::Test);

}

// Called every frame
void AS_SpawnItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

