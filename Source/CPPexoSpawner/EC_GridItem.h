// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_GridManager.h"
#include "EC_GridItem.generated.h"
//class AS_GridManager;
UCLASS()
class CPPEXOSPAWNER_API AEC_GridItem : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridInitialized);
	UPROPERTY()
		FOnGridInitialized onGridInitialized;
		UPROPERTY()
		AS_GridManager* grid = nullptr;
public:	
	// Sets default values for this actor's properties
	AEC_GridItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetGrid(AS_GridManager* _grid)
	{
		grid = _grid;
		
		//grid->OnEventTest();
		if (grid)
			onGridInitialized.Broadcast();
			
	}
public:	
	UFUNCTION()
		void Test();
	UFUNCTION()
		void Init();
};
