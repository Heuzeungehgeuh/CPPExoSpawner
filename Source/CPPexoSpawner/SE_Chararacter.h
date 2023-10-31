// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include <GameFramework/SpringArmComponent.h>
#include "SE_Chararacter.generated.h"

class ASE_Spawner;

UCLASS()
class CPPEXOSPAWNER_API ASE_Chararacter : public ACharacter
{
	GENERATED_BODY()
#pragma
		UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArmComponent = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> cameraComponent = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputMappingContext> inputMappingContext = nullptr;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 200;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> inputToMoveRgt = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> inputToMoveFwd = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputAction> inputToRotate = nullptr;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 80;
	UPROPERTY()
		FTimerHandle timerTick;
	UPROPERTY(EditAnywhere)
		float timerTickRate = 0.5f;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> allActors;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> actorToFind = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ASE_Spawner> actorToSpawn = nullptr;

	/*UPROPERTY(EditAnywhere)
		(Meta = (UImin = "0", CalmpMin = "0", UImax = 20, ClampMax = "20"));*/
public:
	// Sets default values for this character's properties
	ASE_Chararacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn(const FInputActionValue& _value);
	void MoveForward(const FInputActionValue& _value);
	void MoveRight(const FInputActionValue& _value);
	void Rotate(const FInputActionValue& _value);
	void InitInput();
	void customTick();
	void PlayerGameLoop();
	void DrawDebugPlayerTarget(AActor* _target);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
