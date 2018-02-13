// Fill out your copyright notice in the Description page of Project Settings.

#include "TweenFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

/**
 * Creates a UTweenComponent and attach it to an Actor
 * @param actor
 */

UTweenComponent * UTweenFunctionLibrary::CreateTween(AActor * actor)
{
	UTweenComponent* tween = NewObject<UTweenComponent>(actor, UTweenComponent::StaticClass());

	//	actor->AddInstanceComponent(tween);
	actor->AddOwnedComponent(tween);
	tween->RegisterComponent();

	return tween;
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
	if (UWorld* World = GEngine->GetWorldFromContextObject(worldContextObject))
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
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, vOrigin, vTarget, targetTime, worldspace, loop, teleportPhysics);

	if (!CreateLatentAction(tween, worldContextObject, latentInfo))
	{
		tween->Destroy();
	}

	return tween;
}


UTweenComponent * UTweenFunctionLibrary::TweenRotation(AActor * actor, FRotator rOrigin, FRotator rTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode, float targetTime, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, rOrigin, rTarget, targetTime, loop, teleportPhysics);

	if (!CreateLatentAction(tween, worldContextObject, latentInfo))
	{
		tween->Destroy();
	}

	return tween;
}


UTweenComponent * UTweenFunctionLibrary::TweenTransform(AActor * actor, FTransform tOrigin, FTransform tTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode, float targetTime, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, tOrigin, tTarget, targetTime, loop, teleportPhysics);

	if (!CreateLatentAction(tween, worldContextObject, latentInfo))
	{
		tween->Destroy();
	}

	return tween;
}

