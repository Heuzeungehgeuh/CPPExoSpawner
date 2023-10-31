// Fill out your copyright notice in the Description page of Project Settings.


#include "SE_SpawnObject.h"

// Sets default values
ASE_SpawnObject::ASE_SpawnObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	staticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASE_SpawnObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASE_SpawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

