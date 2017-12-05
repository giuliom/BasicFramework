// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicUtils.h"
#include "GameFramework/Actor.h"


void UBasicUtils::SetActorEnabled(AActor* actor, bool enabled)
{
	actor->SetActorTickEnabled(enabled);
	actor->SetActorHiddenInGame(!enabled);
	actor->SetActorEnableCollision(enabled);

	TSet<UActorComponent*> components = actor->GetComponents();

	for (auto& comp : components)
	{
		comp->SetComponentTickEnabled(enabled);
	}
}

UActorComponent * UBasicUtils::LineTraceComponent(FHitResult & outHit, AActor* actor, UClass * componentClass, const FVector & start, const FVector & end, ECollisionChannel channel, bool ignoreActor)
{
	FCollisionObjectQueryParams objParams;
	objParams.AddObjectTypesToQuery(channel);

	FCollisionQueryParams params;
	if (ignoreActor) params.AddIgnoredActor(actor);

	bool bHit = actor->GetWorld()->LineTraceSingleByObjectType(outHit, start, end, objParams, params);

	if (bHit)
	{
		// Hit.Actor contains a weak pointer to the Actor that the trace hit
		return outHit.Actor.Get()->GetComponentByClass(componentClass);
	}
	else
	{
		return nullptr;
	}
}
