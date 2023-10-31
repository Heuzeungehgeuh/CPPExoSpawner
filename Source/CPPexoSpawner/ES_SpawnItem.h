// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ES_SpawnItem.generated.h"

UCLASS()
class CPPEXOSPAWNER_API AES_SpawnItem : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, Category = "Settings|Body")
		TObjectPtr<UStaticMeshComponent> staticMesh = nullptr;
		UPROPERTY(EditAnywhere)
		TArray<UStaticMesh*> allMeshes;
		UPROPERTY(EditAnywhere)
		int index = 0;
		UPROPERTY(EditAnywhere)
		TArray<UMaterialInterface*> allMaterials;
		UPROPERTY(EditAnywhere)
			int indexM = 0;
		UPROPERTY(EditAnywhere)
			FColor meshColor = FColor::MakeRandomColor();
		
		/*UPROPERTY(EditAnywhere)
		AActor* actorToDestroy = TSubclassOf<AES_SpawnItem>;*/

public:	
	// Sets default values for this actor's properties
	AES_SpawnItem();
	void SwapMesh();
	void SwapMaterial();
	void SetInvisiblity(bool _value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};

