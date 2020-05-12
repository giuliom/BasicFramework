// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicInteractionComponent.h"

// Sets default values for this component's properties
UBasicInteractionComponent::UBasicInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


void UBasicInteractionComponent::Execute_Implementation(UObject * caller, UActorComponent* component, UBasicInteractionType* interactionType)
{
	if (!bExecutionEnabled) return;
	
	if (OnExecution.IsBound()) OnExecution.Broadcast(caller, component, interactionType);
	ExecuteInternal(caller, component, interactionType);

	if (OnInteractionCompleted.IsBound()) OnInteractionCompleted.Broadcast(caller, component, interactionType);

}

void UBasicInteractionComponent::OnFocusBegin_Implementation(AActor * byActor)
{
	bFocused = true;
}

void UBasicInteractionComponent::OnFocusEnd_Implementation(AActor * byActor)
{
	bFocused = false;
}





