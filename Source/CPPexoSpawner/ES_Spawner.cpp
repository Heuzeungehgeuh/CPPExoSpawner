// Fill out your copyright notice in the Description page of Project Settings.


#include "ES_Spawner.h"
#include "ES_SpawnItem.h"
#include <DrawDebugHelpers.h>
#include "GameFramework/PlayerController.h"
#include <Kismet/GameplayStatics.h>

AES_Spawner::AES_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	staticMesh->SetupAttachment(RootComponent);
}


void AES_Spawner::BeginPlay()
{
	Super::BeginPlay();
	EnableInput(GetWorld()->GetFirstPlayerController());

	// Attacher la fonction de gestion de l'entrée souris
	/*APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->InputComponent->BindAction("RightClick", IE_Pressed, this, &AES_Spawner::OnMouseClick);*/
	//PlayerController->InputComponent->BindAction("LeftClick", IE_Released, this, &AES_Spawner::OnMouseRelease);
	//onTimerElapsed.AddDynamic(this, &AES_Spawner::Spawn); // => on abonne la fonction Spawn à onTimerElapse 
	onTimerElapsed.AddDynamic(this, &AES_Spawner::SpawnGrille);
	onSpawnCount.AddDynamic(this, &AES_Spawner::GetCountSpawn);
	
}

void AES_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Debug();
	currentTime = IncreaseTime(currentTime, timerSpawnRate);
	
}


void AES_Spawner::FindGameItems()
{
	UGameplayStatics::GetAllActorsOfClass(this, actorToFind, allActors);
}



void AES_Spawner::Grille(int Lines, int Colonnes, float X, float Y)
{
	//int _localSpawn = 0;
	//if (spawnItem < maxSpawnChoose)
		//spawnItem = _localSpawn;
	for (int i = 0; i < Lines; ++i)
	{
		//if (spawnItem < maxSpawnChoose)
		for (int i1 = 0; i1 < Colonnes; ++i1)
		{

			FVector spawnLocation = GetActorLocation(); // Emplacement de base

			spawnLocation.X += i1 * X; // Colonne
			spawnLocation.Y += i * Y;

			//AES_SpawnItem* newSpawnItem = GetWorld()->SpawnActor<AES_SpawnItem>(actorToSpawn, SpawnLocation, FRotator::ZeroRotator);
			
			
			
			//SpawnGrille(spawnLocation);
			//onTimerElapsed.AddDynamic(this, &AES_Spawner::SpawnGrille); //VOIR SI LEVENT MARCH
			
			onTimerElapsed.Broadcast(spawnLocation);

			//if (newSpawnItem)spawnItem++;
		}
	}
}

void AES_Spawner::SpawnGrille(const FVector& _localSpawn)
{
	if(spawnItem < maxSpawnChoose)
	{
		AES_SpawnItem* newSpawnItem = GetWorld()->SpawnActor<AES_SpawnItem>(actorToSpawn, _localSpawn, FRotator::ZeroRotator);
		if (newSpawnItem)
		onSpawnCount.Broadcast(1);
	}
}

#pragma region Boucle Custom
float AES_Spawner::IncreaseTime(const float& _currentTime, const float& _maxTime)
{
	float _newTime = _currentTime + GetWorld()->DeltaTimeSeconds;
	if (_newTime >= _maxTime)
	{
		/*FindGameItems();
		if (allActors =20)Break;*/
		if (useDecreasingSpawnRate)							//if(useDecreasingSpawnRate)
			AddSpawnRate(spawnRateDecreasingValue);			//	{
															//		AddSpawnRate(spawnRateDecreasingValue);
		_newTime = 0;										//	}
		
			//FindGameItems();
		//onTimerElapsed.Broadcast(); // => Execute L'event // ici ON supprime les // pour montrer l'exercice des evenement /!\
			//Spawn();

		/*int _sizeMax = 2;
		for (int i = 0; i < 2; i++)
		{
		}*/
		Grille(line, colonne, interX, interY);
		//PlayerGameLoop();
		
		//Spawn();
	}
	return _newTime;
}
void AES_Spawner::AddSpawnRate(const float& _toAdd)
{
	timerSpawnRate += _toAdd;
	if (timerSpawnRate <= minSpawnRate)
		timerSpawnRate = minSpawnRate;
}
#pragma endregion

#pragma region DEBUG
void AES_Spawner::DebugSpawnLocation(const FVector& _location)
{
	DrawDebugSphere(GetWorld(), _location, 100, 15, FColor::Green, true, timerSpawnRate, 0, 2);
}

void AES_Spawner::Debug()
{
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector::OneVector * 50, FColor::Red, false, -1, 0, 2);

}
#pragma endregion

#pragma region Fonction Useless
void AES_Spawner::OnMouseClick()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, MouseLocation, MouseLocation + MouseDirection * 10000, ECC_Visibility, CollisionParams))
	{
		SetActorLocation(HitResult.ImpactPoint);
	}
}
void AES_Spawner::Spawn()
{
	
	if (spawnItem < 20)
	{
		const FVector _localToSpawn = useCustomSpawnLocation ? customSpawnLocation : GetActorLocation();
		DebugSpawnLocation(_localToSpawn);
		AES_SpawnItem* newSpawnItem = GetWorld()->SpawnActor<AES_SpawnItem>(actorToSpawn, _localToSpawn, FRotator::ZeroRotator); 
		UE_LOG(LogTemp, Warning, TEXT("Spawn"));
		if (newSpawnItem)spawnItem++;
		
	}
}
void AES_Spawner::PlayerGameLoop()
{
	//Spawn();
	//Grille();
	
	//int sizeMax = 2;														//allActors.Num();
	//for (int i = 0; i <= sizeMax; i++)
	//{
	//	//if (i == sizeMax)break;		
	//																	//if (!_target)continue;
	//	Spawn();																		//AActor* _target = allActors[_index];
	//	// continue fait reprendre la boucle du début, break fait sortir de la boucle , le return sort completement de la fonction
	//}

}
#pragma endregion