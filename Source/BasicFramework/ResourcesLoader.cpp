// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourcesLoader.h"
#include "Runtime/Engine/Classes/Engine/AssetManager.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


/**
* Load a SoundWave, checking if it's already loaded first the start a blocking load.
*
* @param owner the object that will handle the Sound, usually the caller of the function
* @param assetPath complete assetPath+name of the asset.
* @return the SoundWave or nullptr if not found
*/
USoundWave * UResourcesLoader::LoadSound(UObject* owner, FString& assetPath)
{
	/** Find the assets if it's already loaded */
	USoundWave* sound = FindObject<USoundWave>(owner, *assetPath);

	if (sound == nullptr)
	{
		sound = LoadObject<USoundWave>(owner, *assetPath);
	}
	return sound;
}


UObject* UResourcesLoader::LoadAsset(TAssetPtr<UObject> asset)
{
	if (asset.IsPending())
	{
		const FSoftObjectPath& aRef = asset.ToSoftObjectPath();
		return UAssetManager::GetStreamableManager().LoadSynchronous(aRef);
	}
	return asset.Get();
}

TAssetPtr<UObject> UResourcesLoader::LoadAssetAsync(TAssetPtr<UObject> asset, UObject * worldContextObject, FLatentActionInfo latentInfo)
{
	FStreamableDelegate sdelegate = nullptr;
	if (UWorld* World = GEngine->GetWorldFromContextObjectChecked(worldContextObject))
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		//if (LatentActionManager.FindExistingAction<FAsyncResourceAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == NULL)
		{
			LatentActionManager.AddNewAction(latentInfo.CallbackTarget, latentInfo.UUID, new FAsyncResourceAction(asset, latentInfo));
		}
	}
	LoadAssetAsync(asset, sdelegate, FStreamableManager::DefaultAsyncLoadPriority);
	return asset;
}


TAssetPtr<UObject> UResourcesLoader::LoadAssetAsync(TAssetPtr<UObject> asset, FStreamableDelegate& delegateToCall, TAsyncLoadPriority Priority)
{
	if (asset.IsPending())
	{
		const FSoftObjectPath& aRef = asset.ToSoftObjectPath();
		UAssetManager::GetStreamableManager().RequestAsyncLoad( aRef, delegateToCall, Priority);
	}
	return asset;
}


