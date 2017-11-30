// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPawn.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABasicPawn::ABasicPawn(const FObjectInitializer & ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	defaultVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DefaultVisibleComponent"));
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	

}

// Called when the game starts or when spawned
void ABasicPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//----------------------- INPUT PROCESSING METHODS -----------------------

void ABasicPawn::ProcessInputForward_Internal(float val)
{
}

void ABasicPawn::ProcessInputRight_Internal(float val)
{
}

