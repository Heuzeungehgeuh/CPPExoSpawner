// Fill out your copyright notice in the Description page of Project Settings.


#include "ES_SpawnItem.h"

// Sets default values
AES_SpawnItem::AES_SpawnItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");

	staticMesh->SetupAttachment(RootComponent);
	//GetStaticMeshComponent()->SetMaterial


}

void AES_SpawnItem::SwapMesh()
{
	index++;
	const int _size = allMeshes.Num();
	index %= _size;
	UE_LOG(LogTemp, Warning, TEXT("%i"), index)
	staticMesh->SetStaticMesh(allMeshes[index]);
}

// Called when the game starts or when spawned
void AES_SpawnItem::BeginPlay()
{
	Super::BeginPlay();
	//SwapMesh();
	//SwapMaterial();
	UMaterialInstanceDynamic* _matInstance = staticMesh->CreateDynamicMaterialInstance(0);
	//FLinearColor meshColor = _matInstance;
	if (!_matInstance)return;
	_matInstance->SetVectorParameterValue("Base Color", meshColor);
}

// Called every frame
void AES_SpawnItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//UMaterialInterface* GetRandomMaterial()
//{
//	TArray<UMaterialInterface*> PossibleMaterials;
//	
//	int RandomIndex = FMath::RandRange(0, PossibleMaterials.Num() - 1);
//
//	return PossibleMaterials[RandomIndex];
//}

void AES_SpawnItem::SwapMaterial()
{
	indexM++;
	const int _size = allMaterials.Num();
	indexM %= _size;
	UE_LOG(LogTemp, Warning, TEXT("%i"), indexM)
		//staticMesh->SetStaticMesh(allMaterials[indexM]);
	UMaterialInstanceDynamic* _matInstance = staticMesh->CreateDynamicMaterialInstance(0);
	//FLinearColor meshColor = _matInstance;
	if (!_matInstance)return;
	_matInstance->SetVectorParameterValue("Base Color", meshColor);
	//GetStaticMeshComponent()->SetMaterial(0, allMaterials[indexM]);
	//AES_SpawnItem->GetStaticMeshComponent()->SetMaterial(0, RandomMaterial);
}

void AES_SpawnItem::SetInvisiblity(bool _value)
{
	if (!staticMesh)return;
	staticMesh->SetVisibility(_value);
	//staticMesh->ToggleVisibility();
	/*AActor* actorToDestroy = AES_SpawnItem&;
	if (actorToDestroy)
	{
		actorToDestroy->Destroy();
	}*/
	//rendre invisible
	//SetActorHiddenInGame(true);

	////rend les collision OFF
	//SetActorEnableCollision(false);
}


