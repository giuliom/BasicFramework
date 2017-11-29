// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/Sound/SoundWave.h"
#include "Runtime/Engine/Classes/Engine/StreamableManager.h"
#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "LatentActions.h"
#include "ResourcesLoader.generated.h"

/**
 * @author @Giulio_M
 *
 * BlueprintFunctionLibrary handling all the resource loading both sync and async in Blueprint and C++ code.
 * AsyncLoading in Blueprint is handled with latent blueprintfunctions. FAsyncResourceAction is the latent action
 */

class FAsyncResourceAction : public FPendingLatentAction
{
public:
	TAssetPtr<UObject> asset;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	FAsyncResourceAction(TAssetPtr<UObject> asset, const FLatentActionInfo& LatentInfo)
		: asset(asset)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
	{}

	virtual void UpdateOperation(FLatentResponse& Response) override
	{
		Response.FinishAndTriggerIf(asset.Get() != nullptr , ExecutionFunction, OutputLink, CallbackTarget);
	}

};


UCLASS(Blueprintable)
class BASICFRAMEWORK_API UResourcesLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Resources Loading", meta = (HidePin = "owner", DefaultToSelf = "owner"))
	static USoundWave* LoadSound(UObject* owner, FString& assetPath);

	UFUNCTION(BlueprintCallable, Category = "Resources Loading")
	static UObject* LoadAsset(TAssetPtr<UObject> asset);

	UFUNCTION(BlueprintCallable, Category = "Resources Loading", meta = (Latent, LatentInfo = "LatentInfo", HidePin = "worldContextObject", DefaultToSelf = "worldContextObject"))
	static TAssetPtr<UObject> LoadAssetAsync(TAssetPtr<UObject> asset, UObject * worldContextObject, FLatentActionInfo latentInfo);

	static TAssetPtr<UObject> LoadAssetAsync(TAssetPtr<UObject> asset, FStreamableDelegate& delegateToCall, TAsyncLoadPriority Priority);

};
