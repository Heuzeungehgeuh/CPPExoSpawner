
// Fill out your copyright notice in the Description page of Project Settings.


#include "SE_Chararacter.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include <DrawDebugHelpers.h>
#include "C:/Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "C:/Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"

// Sets default values
ASE_Chararacter::ASE_Chararacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("camera");
	springArmComponent->SetupAttachment(RootComponent);
	cameraComponent->SetupAttachment(springArmComponent);
}

// Called when the game starts or when spawned
void ASE_Chararacter::BeginPlay()
{
	Super::BeginPlay();
	InitInput();
	GetWorld()->GetTimerManager().SetTimer(timerTick, this, &ASE_Chararacter::customTick, timerTickRate, true);
	//DrawDebugPlayerTarget(_target);
}

void ASE_Chararacter::Spawn(const FInputActionValue& _value)
{
	/*const FVector _locationToSpawn = GetActorLocation() + GetActorForwardVector() * 100;
	ASE_Spawner* _spawned = GetWorld()->SpawnActor<ASE_Spawner>(actorToSpawn, _locationToSpawn, FRotator::ZeroRotator);
	if (!_spawned)return;
	allActors.Add(_spawned);*/
}

// Called every frame
void ASE_Chararacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASE_Chararacter::MoveForward(const FInputActionValue& _value)
{

	const FVector _fwd = GetActorForwardVector();
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _movementValue = _value.Get<float>() * _delta * moveSpeed;
	AddMovementInput(_fwd, _movementValue);

}

void ASE_Chararacter::MoveRight(const FInputActionValue& _value)
{
	const FVector _rgt = GetActorRightVector();
	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _movementValue = _value.Get<float>() * _delta * moveSpeed;
	AddMovementInput(_rgt, _movementValue);
}

void ASE_Chararacter::Rotate(const FInputActionValue& _value)
{

	const float _delta = GetWorld()->DeltaTimeSeconds;
	const float _rotationValue = _value.Get<float>() * _delta * rotationSpeed;
	AddControllerYawInput(_rotationValue);

}

void ASE_Chararacter::InitInput()
{
	ULocalPlayer* _localPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
	if (!_localPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _inputSystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_inputSystem)return;
	_inputSystem->AddMappingContext(inputMappingContext, 0);

}

void ASE_Chararacter::customTick()
{
	PlayerGameLoop();
}

void ASE_Chararacter::PlayerGameLoop()
{
	const int _size = allActors.Num();
	for (int _index = 0; _index < _size; _index++)
	{
		AActor* _target = allActors[_index];
		if (!_target)continue;
		DrawDebugPlayerTarget(_target);
	}
}

void ASE_Chararacter::DrawDebugPlayerTarget(AActor* _target)
{
	if (!_target)return;
	const UWorld* _world = GetWorld();
	if (!_world)return;
	const FVector _currentLocation = GetActorLocation();
	const FVector _targetLocation = _target->GetActorLocation();
	DrawDebugBox(_world, _targetLocation, FVector::OneVector * 100, FColor::Red, false, timerTickRate, 0, 2);
	//FVector::onevector peut etre remplacer par un (100,100,100)
	DrawDebugLine(_world, _currentLocation, _targetLocation, FColor::Magenta, false, timerTickRate, 0, 2);
}


// Called to bind functionality to input
void ASE_Chararacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* _inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	_inputCompo->BindAction(inputToMoveFwd, ETriggerEvent::Triggered, this, &ASE_Chararacter::MoveForward);
	_inputCompo->BindAction(inputToMoveRgt, ETriggerEvent::Triggered, this, &ASE_Chararacter::MoveRight);
	_inputCompo->BindAction(inputToRotate, ETriggerEvent::Triggered, this, &ASE_Chararacter::Rotate);
	/*_inputCompo->BindAction(inputToInteract, ETriggerEvent::Triggered, this, &ADM_GameCHARCOR::Interact);
	_inputCompo->BindAction(inputToInteract, ETriggerEvent::Triggered, this, &ADM_GameCHARCOR::Spawn);*/
}

