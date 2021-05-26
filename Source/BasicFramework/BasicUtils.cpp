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

AActor * UBasicUtils::FindActorByName(FString name)
{
	return FindObject<AActor>(nullptr, *name);;
}

TArray<AActor*> UBasicUtils::FindActorsByTag(UWorld* world, FName tag)
{
	check(world != nullptr);

	TArray<AActor*> list;

	for (TActorIterator<AActor> It(world); It; ++It)
	{
		AActor* actor = *It;
		if (actor->ActorHasTag(tag))
		{
			list.Add(actor);
		}
	}
	return list;
}

UActorComponent * UBasicUtils::LineTraceComponent(FHitResult & outHit, AActor* actor, UClass * componentClass, const FVector & start, const FVector & end, ECollisionChannel channel, bool worldStaticCollision, bool worldDynamicCollision, bool ignoreActor)
{
	FCollisionObjectQueryParams objParams;
	if (worldStaticCollision) objParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	if (worldDynamicCollision) objParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	objParams.AddObjectTypesToQuery(channel);

	FCollisionQueryParams params;
	if (ignoreActor) params.AddIgnoredActor(actor);

	bool bHit = actor->GetWorld()->LineTraceSingleByObjectType(outHit, start, end, objParams, params);

	if (bHit)
	{
		// Hit.Actor contains a weak pointer to the Actor that the trace hit
		return outHit.GetActor()->GetComponentByClass(componentClass);
	}
	else
	{
		return nullptr;
	}
}

TArray<UActorComponent*> UBasicUtils::LineTraceComponents(FHitResult& outHit, AActor* actor, UClass* componentClass, const FVector& start, const FVector& end, ECollisionChannel channel, bool worldStaticCollision, bool worldDynamicCollision, bool ignoreActor)
{

	FCollisionObjectQueryParams objParams;
	if (worldStaticCollision) objParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	if (worldDynamicCollision) objParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	objParams.AddObjectTypesToQuery(channel);

	FCollisionQueryParams params;
	if (ignoreActor) params.AddIgnoredActor(actor);

	bool bHit = actor->GetWorld()->LineTraceSingleByObjectType(outHit, start, end, objParams, params);

	if (bHit)
	{
		// Hit.Actor contains a weak pointer to the Actor that the trace hit
		return outHit.GetActor()->GetComponentsByClass(componentClass);
	}
	
	return TArray<UActorComponent*>();
}
