// Fill out your copyright notice in the Description page of Project Settings.


#include "ES_Eater.h"
#include "ES_SpawnItem.h"
#include "Kismet/GameplayStatics.h"
#include <DrawDebugHelpers.h>

// Sets default values
AES_Eater::AES_Eater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	staticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AES_Eater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AES_Eater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindGameItems();
	PlayerGameLoop();
	currentTime = IncreaseTime(currentTime, timerSpawnRate);
}

void AES_Eater::FindGameItems()
{
	UGameplayStatics::GetAllActorsOfClass(this, actorToFind, allActors);
}
void AES_Eater::PlayerGameLoop()
{
	const int _size = allActors.Num();
	for (int _index = 0; _index < _size; _index++)
	{
		AActor* _target = allActors[_index];
		if (!_target)continue;
		// continue fait reprendre la boucle du début, break fait sortir de la boucle , le return sort completement de la fonction
		//DrawDebugPlayerTarget(_target);
		ChooseTarget();
		ChangeColor(_target);
		PlayerDetectionBehaviour(_target);
	}
}

void AES_Eater::PlayerDetectionBehaviour(AActor* _target)
{
	if (!_target)return;
	const FVector _currentLocation = GetActorLocation();
	const FVector _targetLocation = _target->GetActorLocation();
	const float _distance = FVector::Dist(_currentLocation, _targetLocation);
	const bool _isInRange = _distance <= minDistanceAllowed;
	if (!_isInRange)return;
	AES_SpawnItem* _item = Cast<AES_SpawnItem>(_target);
	if (!_item)return;
	//_item->ItemBehaviour();
	_item->Destroy();
	//_item->SetInvisiblity(false);
}

void AES_Eater::ChooseTarget()
{
	int randomIndex = FMath::RandRange(0, allActors.Num() - 1);
	AActor* randomTarget = allActors[randomIndex];
	if (randomTarget)
	{
		FVector targetLocation = randomTarget->GetActorLocation();
		//DrawDebugSphere()
		//DrawDebugSphere(GetWorld(), targetLocation, 100, 15, FColor::Green, true, timerSpawnRate, 0, 2);
		
		//ici mettre essaie LERP PROGRESS
		//FVector startLocation = GetActorLocation();
		//FVector lerpedLocation = FMath::Lerp(startLocation, targetLocation, alpha);						//IncreaseTime(currentTime, timerSpawnRate));
		//SetActorLocation(lerpedLocation);

		/*if(targetLocation != FVector::ZeroVector)
				LerpProgress(targetLocation);*/
		
		SetActorLocation(targetLocation);
	}
}

void AES_Eater::ChangeColor(AActor* _target)
{ // ICI on fait une fonction pour changer la couleur a chaque fois que le cube mange une bille il prend ça couleur
	//if (!_target)return;
	//
	//UMaterialInterface* _sourceMaterial = _target->GetMeshComponent->GetMaterial(0);
	//UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(_sourceMaterial, _target);
	//AES_Eater*->GetMeshComponent()->SetMaterial(0, DynamicMaterial);
	////UE_LOG(LogTemp, Warning, TEXT("The Eater change Color"));
	//if (DynamicMaterial)
	//{
	//	DynamicMaterial->SetVectorParameterValue("BaseColor", _sourceMaterial);
	//}
}

void AES_Eater::LerpProgress(const FVector& _locationToRush)
{
	// ICI on fait une fonction qui fait que notre acteur va avancer plutot que de se teleporter sur une position
	
	FVector startLocation = GetActorLocation(); // Position de départ
	FVector endLocation = _locationToRush;   // Position de fin
	//float alpha = 0.0f;        
	float moveDuration = 2.0f;						//IncreaseTime(currentTime, timerSpawnRate);  
	float CurrentTime = 0.0f;  
	//Fait freeze Unreal
	while (CurrentTime < moveDuration)
	{
		alpha = CurrentTime / moveDuration;
		FVector lerpedLocation = FMath::Lerp(startLocation, endLocation, alpha);
		SetActorLocation(lerpedLocation);
	}
}

void AES_Eater::EnlargeYourCube()
{// ICI on Fais une Fonction qui a chaque fois que le cube mange un bille il grossisse

}
#pragma region Boucle Custom
float AES_Eater::IncreaseTime(const float& _currentTime, const float& _maxTime)
{
	float _newTime = _currentTime + GetWorld()->DeltaTimeSeconds;
	if (_newTime >= _maxTime)
	{
		
		if (useDecreasingSpawnRate)							
			AddSpawnRate(spawnRateDecreasingValue);			
		
		_newTime = 0;	
		//FindGameItems();
		//PlayerGameLoop();

	}
	return _newTime;
}
void AES_Eater::AddSpawnRate(const float& _toAdd)
{
	timerSpawnRate += _toAdd;
	if (timerSpawnRate <= minSpawnRate)
		timerSpawnRate = minSpawnRate;
}
#pragma endregion