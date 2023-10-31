// Fill out your copyright notice in the Description page of Project Settings.

#include "S_Spawner.h"
#include "S_SpawnItem.h"
#include <DrawDebugHelpers.h>
// Sets default values


AS_Spawner::AS_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	customSpawnLocationGizmo = CreateDefaultSubobject<USceneComponent>("CustomSpawnLocationGizmo");
	//customSpawnLocationGizmo->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AS_Spawner::BeginPlay()
{
	Super::BeginPlay();
	//GetWorld()->GetTimerManager().SetTimer(timerSpawn, this, &AS_Spawner::Spawn, timerSpawnRate, true);
	onTimerElapsed.AddDynamic(this, &AS_Spawner::Spawn); // => on abonne la fonction Spawn à onTimerElapse 
}


// Called every frame
void AS_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Spawn();
	currentTime = IncreaseTime(currentTime, timerSpawnRate);
	Debug();
}

FVector AS_Spawner::GetSpawnLocation()
{
	customSpawnLocation = customSpawnLocationGizmo->GetComponentLocation();
	return useCustomSpawnLocation ? customSpawnLocation : GetActorLocation();
	
}

float AS_Spawner::IncreaseTime(const float& _currentTime, const float& _maxTime)
{
	float _newTime = _currentTime + GetWorld()->DeltaTimeSeconds;
	if(_newTime >= _maxTime)
	{
		if (useDecreasingSpawnRate)							//if(useDecreasingSpawnRate)
			AddSpawnRate(spawnRateDecreasingValue);			//	{
															//		AddSpawnRate(spawnRateDecreasingValue);
		_newTime = 0;										//	}
		//Spawn();
		onTimerElapsed.Broadcast(); // => Execute L'event
		
	}
	return _newTime;
}

void AS_Spawner::SetCurrentTime(const float& _value)
{
	currentTime = _value;
}

void AS_Spawner::DebugSpawnLocation(const FVector& _location)
{

	DrawDebugSphere(GetWorld(), _location, 100, 15, FColor::Green, false, timerSpawnRate, 0, 2);
}

void AS_Spawner::Debug()
{
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector::OneVector * 50, FColor::Red, false, -1, 0, 2);

}

void AS_Spawner::AddSpawnRate(const float& _toAdd)
{
	timerSpawnRate += _toAdd;
	if (timerSpawnRate <= minSpawnRate)
		timerSpawnRate = minSpawnRate;
}

void AS_Spawner::AddSpawnCount(const int& _toAdd)
{
	currentSpawnCount += _toAdd;
	//if (currentSpawnCount > spawnCountLimit) //peut etre deplier avec les accolade mais si plusieur ligne accolade obligatoire
	//	currentSpawnCount = spawnCountLimit;
}


void AS_Spawner::Spawn()
{
	if (useSpawnCountLimit && !GetIsSpawnAllowed())return;
	//1ER Façon ternaire
	//const FVector _localToSpawn = useCustomSpawnLocation ? customSpawnLocation : GetActorLocation();


	const FVector _localToSpawn = GetSpawnLocation();


	//2eme façon Ternaire déplié
	/*FVector _localToSpawn = FVector(0);
	if (useCustomSpawnLocation)
	{
		_localToSpawn = customSpawnLocation;
	}
	else
	{
		_localToSpawn = GetActorLocation();
	}*/



	DebugSpawnLocation(_localToSpawn);
	AS_SpawnItem* _spawned = GetWorld()->SpawnActor<AS_SpawnItem>(actorToSpawn, _localToSpawn, FRotator::ZeroRotator);
	if (!_spawned)return;
	UE_LOG(LogTemp, Warning, TEXT("Spawn"));
	AddSpawnCount(1);

}

