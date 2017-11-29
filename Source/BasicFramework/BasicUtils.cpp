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

