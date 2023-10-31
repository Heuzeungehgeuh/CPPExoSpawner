// Fill out your copyright notice in the Description page of Project Settings.


#include "EC_GridItem.h"

// Sets default values
AEC_GridItem::AEC_GridItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEC_GridItem::BeginPlay()
{
	Super::BeginPlay();
	onGridInitialized.AddDynamic(this, &AEC_GridItem::Init);
}

// Called every frame
void AEC_GridItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEC_GridItem::Test()
{
	UE_LOG(LogTemp, Warning, TEXT("Item Event"));
}

void AEC_GridItem::Init()
{
	if(!grid)return;
	grid->OnEventTest().AddDynamic(this, &AEC_GridItem::Test);
}



