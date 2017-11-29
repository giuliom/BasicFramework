// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicLog.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "DrawDebugHelpers.h"

//General Log
DEFINE_LOG_CATEGORY(Default);

//Logging during startup
DEFINE_LOG_CATEGORY(Startup);

//Logging for AI 
DEFINE_LOG_CATEGORY(AI);

//Logging for services
DEFINE_LOG_CATEGORY(Services);


void UBasicLog::Log(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(Default, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(Startup, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AI, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(Services, Log, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogWarning(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(Default, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(Startup, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AI, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(Services, Warning, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogError(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(Default, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(Startup, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AI, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(Services, Error, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogScreenDebug(FString& message, float displayTime)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Turquoise, message);

}

