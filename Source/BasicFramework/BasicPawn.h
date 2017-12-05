// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/DefaultPawn.h"
#include "BasicPawnInterface.h"
#include "BasicPawn.generated.h"

/**
* @author Giulio_M
* Basic Pawn class for first person adventure games
*
*/
UCLASS(Blueprintable)
class BASICFRAMEWORK_API ABasicPawn : public ADefaultPawn, public IBasicPawnInterface
{
	GENERATED_BODY()

protected:

	UCameraComponent* cameraComponent = nullptr;

public:
	// Sets default values for this pawn's properties
	ABasicPawn(const FObjectInitializer & ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//----------------------- INPUT PROCESSING METHODS -----------------------

	virtual void ProcessInputForward_Internal(float val) override;
	virtual void ProcessInputRight_Internal(float val) override;

	
};
