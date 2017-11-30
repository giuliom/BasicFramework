// Fill out your copyright notice in the Description page of Project Settings.

#include "TweenFunctionLibrary.h"
#include "GameFramework/Actor.h"

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


UTweenComponent * UTweenFunctionLibrary::TweenLocation(AActor * actor, FVector vOrigin, FVector vTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, tdelegate, vOrigin, vTarget, targetTime, worldspace, loop, teleportPhysics);
	return tween;
}


UTweenComponent * UTweenFunctionLibrary::TweenRotation(AActor * actor, FRotator rOrigin, FRotator rTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode, float targetTime, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, tdelegate, rOrigin, rTarget, targetTime, loop, teleportPhysics);
	return tween;
}


UTweenComponent * UTweenFunctionLibrary::TweenTransform(AActor * actor, FTransform tOrigin, FTransform tTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode, float targetTime, bool loop, bool teleportPhysics)
{
	if (actor == nullptr) return nullptr;
	UTweenComponent* tween = CreateTween(actor);
	tween->InitTween(tweenMode, actor, tdelegate, tOrigin, tTarget, targetTime, loop, teleportPhysics);
	return tween;
}

