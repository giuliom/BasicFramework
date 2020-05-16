// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "TweenComponent.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "LatentActions.h"
#include "TweenFunctionLibrary.generated.h"

/**
 * @author Giulio_M
 *
 * A UBlueprintFunctionLibrary that Provides functions that create and instantiate a TweenComponent to an AACtor with the requested tweening mode
 */

class FTweenLatentAction : public FPendingLatentAction
{
public:
	UTweenComponent * tween;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	FTweenLatentAction(UTweenComponent* tween, const FLatentActionInfo& LatentInfo)
		: tween(tween)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
	{}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		bool completed = tween->IsTweenCompleted();
		if (completed) tween->DestroyComponent();
		Response.FinishAndTriggerIf(completed, ExecutionFunction, OutputLink, CallbackTarget);
	}

};


UCLASS()
class BASICFRAMEWORK_API UTweenFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

protected:

		static UTweenComponent* CreateTweenComponent(AActor* actor, TweenContainer* container, UObject* worldContextObject, FLatentActionInfo latentInfo);

		static bool CreateLatentAction(UTweenComponent* tween, UObject * worldContextObject, FLatentActionInfo latentInfo);
	
public:

		UFUNCTION(BlueprintCallable, Category = "Tween", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"))
		static UTweenComponent* TweenLocation(AActor* actor, FVector vOrigin, FVector vTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);
		
		UFUNCTION(BlueprintCallable, Category = "Tween", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"))
		static UTweenComponent* TweenRotation(AActor* actor, FRotator rOrigin, FRotator rTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

		UFUNCTION(BlueprintCallable, Category = "Tween", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"))
		static UTweenComponent* TweenTransform(AActor* actor, FTransform tOrigin, FTransform tTarget, UObject * worldContextObject, FLatentActionInfo latentInfo, ETweenMode tweenMode = ETweenMode::LINEAR, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);
};
