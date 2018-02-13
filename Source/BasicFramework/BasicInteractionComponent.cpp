// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicInteractionComponent.h"
#include "AssertionMacros.h"

// Sets default values for this component's properties
UBasicInteractionComponent::UBasicInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UBasicInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBasicInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBasicInteractionComponent::Execute(UObject * caller, UActorComponent* component, EBasicInteractionType interactionType)
{
	if ((bInteractionInProgress && bSingleInteraction) || !bExecutionAllowed) return;

	PreExecutionSetup();
	
	if (OnPreExecution.IsBound()) OnPreExecution.Broadcast(caller, component, interactionType);

	
	if (!bIsAsync)
	{
		if (OnExecution.IsBound()) OnExecution.Broadcast(caller, component, interactionType);
		if (OnPostExecution.IsBound()) OnPostExecution.Broadcast(caller, component, interactionType);

		PostExecutionSetup(interactionType);
	}
	else 
	{
		/** ATTENTION if async make sure the following delegates must be fired sequentially inside each other.
		 Also OnPostExecution must call  PostExecutionSetup() TODO: bind to delegate
		 */
		ensureMsgf(OnPreExecution.IsBound() == OnExecution.IsBound() == OnPostExecution.IsBound(), TEXT("BasicInteractionComponent: if Async the delegated must be fired sequentially inside each other"));
		if (!OnPostExecution.IsBound()) PostExecutionSetup(interactionType);
	}


}

void UBasicInteractionComponent::PreExecutionSetup()
{
	bInteractionInProgress = true;
}

void UBasicInteractionComponent::PostExecutionSetup(EBasicInteractionType interactionType)
{
	bInteractionInProgress = false;
}




