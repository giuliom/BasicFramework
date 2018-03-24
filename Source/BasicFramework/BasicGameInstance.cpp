// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicGameInstance.h"


void UBasicGameInstance::Init()
{
	UGameInstance::Init();

	//FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UBasicGameInstance::ShowLoadingScreen);
	//FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UBasicGameInstance::HideLoadingScreen);
}

void UBasicGameInstance::ShowLoadingScreen(const FString & levelName)
{

	if (loadingWidgetClass != nullptr) 
	{

		//loadingWidget = CreateWidget<UUserWidget>(this, loadingWidgetClass);
	}

	if (loadingWidget != nullptr)
	{
		loadingWidget->AddToViewport();
	}
	
}

void UBasicGameInstance::HideLoadingScreen()
{
	
	if (loadingWidget != nullptr)
	{
		loadingWidget->RemoveFromViewport();
		loadingWidget = nullptr;
	}
	
}
