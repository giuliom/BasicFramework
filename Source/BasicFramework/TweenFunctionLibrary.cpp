// Fill out your copyright notice in the Description page of Project Settings.

#include "TweenFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

/**
 * Creates a UTweenComponent and attach it to an Actor
 * @param actor
 */
inline UTweenComponent* UTweenFunctionLibrary::CreateTweenComponent(AActor* actor, TweenContainer* container, UObject* worldContextObject, FLatentActionInfo latentInfo)
{
	UTweenComponent* component = NewObject<UTweenComponent>(actor, UTweenComponent::StaticClass());
	component->InitContainer(container);

	actor->AddOwnedComponent(component);
	component->RegisterComponent();

	if (!CreateLatentAction(component, worldContextObject, latentInfo))
	{
		component->DestroyComponent();
		component = nullptr;
	}

	return component;
}

/**
* Attach a UTweenComponent to an actor and tween its location. The tween component remove itself automatically when the tween ends.
* UFUNCTION doest not support C++ templates
* 
* @param actor the actor that is getting tweened
* @param vOrigin the initial vector, in this case representing a location
* @param vTarget the target vector
* @param tweenMode the interpolation mode
* @param targetTime the duration of the tween in seconds
* @param worldspace if the tween vectors are in worldspace or local.
* @param loop if the tween must be looping
* @param teleportPhysics if we must use teleportPhysics when updating the location
*/


bool UTweenFunctionLibrary::CreateLatentAction(UTweenComponent * tween, UObject * worldContextObject, FLatentActionInfo latentInfo)
{
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(worldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		LatentActionManager.AddNewAction(latentInfo.CallbackTarget, latentInfo.UUID, new FTweenLatentAction(tween, latentInfo));
		return true;
	}
	else
	{
		return false;
	}
}

UTweenComponent * UTweenFunctionLibrary::TweenLocation(AActor * actor, FVector vOrigin, FVector vTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;

	TweenTemplate<FVector> tween(tweenMode, actor, vOrigin, vTarget, targetTime, worldspace, loop, teleportPhysics);
	TweenLocationContainer* container = new TweenLocationContainer(tween);
	return CreateTweenComponent(actor, container, worldContextObject, latentInfo);
}


UTweenComponent * UTweenFunctionLibrary::TweenRotation(AActor * actor, FRotator rOrigin, FRotator rTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;

	TweenTemplate<FRotator> tween(tweenMode, actor, rOrigin, rTarget, targetTime, worldspace, loop, teleportPhysics);
	TweenRotationContainer* container = new TweenRotationContainer(tween);
	return CreateTweenComponent(actor, container, worldContextObject, latentInfo);
}


UTweenComponent * UTweenFunctionLibrary::TweenTransform(AActor * actor, FTransform tOrigin, FTransform tTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;

	TweenTemplate<FTransform> tween(tweenMode, actor, tOrigin, tTarget, targetTime, worldspace, loop, teleportPhysics);
	TweenTransformContainer* container = new TweenTransformContainer(tween);
	return CreateTweenComponent(actor, container, worldContextObject, latentInfo);
}

