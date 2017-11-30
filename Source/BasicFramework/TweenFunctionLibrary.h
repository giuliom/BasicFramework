// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "TweenComponent.h"
#include "TweenFunctionLibrary.generated.h"

/**
 * @author Giulio_M
 *
 * A UBlueprintFunctionLibrary that Provides functions that create and instantiate a TweenComponent to an AACtor with the requested tweening mode
 */


UCLASS()
class BASICFRAMEWORK_API UTweenFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:
		static UTweenComponent* CreateTween(AActor* actor);
	
public:

		UFUNCTION(BlueprintCallable, Category = "Tween")
		static UTweenComponent* TweenLocation(AActor* actor, FVector vOrigin, FVector vTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);
		
		UFUNCTION(BlueprintCallable, Category = "Tween")
		static UTweenComponent* TweenRotation(AActor* actor, FRotator rOrigin, FRotator rTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool loop = false, bool teleportPhysics = false);

		UFUNCTION(BlueprintCallable, Category = "Tween")
		static UTweenComponent* TweenTransform(AActor* actor, FTransform tOrigin, FTransform tTarget, FTweenDynamicDelegate tdelegate, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool loop = false, bool teleportPhysics = false);

};


