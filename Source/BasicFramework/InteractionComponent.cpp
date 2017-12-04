// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::Execute_Internal(UObject * caller, UActorComponent* component, EBasicInteractionType interactionType)
{
	if ((bInteractionInProgress && bSingleInteraction) || !bExecutionAllowed) return;

	PreExecutionSetup();
	
	PreExecution(caller, component, interactionType);

	/** iIf async the following must be called inside each _Execution() method */
	if (!bIsAsync)
	{
		Execution(caller, component, interactionType);
		PostExecution(caller, component, interactionType);

		PostExecutionSetup(interactionType);
	}


}

void UInteractionComponent::PreExecutionSetup()
{
	bInteractionInProgress = true;
}

void UInteractionComponent::PreExecution_Implementation(UObject * caller, UActorComponent * component, EBasicInteractionType interactionType)
{
	PreExecution_Internal(caller, component, interactionType);
	if (bIsAsync) Execution(caller, component, interactionType);
}

void UInteractionComponent::Execution_Implementation(UObject * caller, UActorComponent * component, EBasicInteractionType interactionType)
{
	PreExecution_Internal(caller, component, interactionType);
	if (bIsAsync) PostExecution(caller, component, interactionType);
}


void UInteractionComponent::PostExecution_Implementation(UObject * caller, UActorComponent * component, EBasicInteractionType interactionType)
{
	PreExecution_Internal(caller, component, interactionType);
	if (bIsAsync) PostExecutionSetup(interactionType);
}

void UInteractionComponent::PostExecutionSetup(EBasicInteractionType interactionType)
{
	bInteractionInProgress = false;
	if (OnExecutionCompleted.IsBound()) OnExecutionCompleted.Broadcast(interactionType);
}




