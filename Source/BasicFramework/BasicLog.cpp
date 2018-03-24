// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicLog.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "DrawDebugHelpers.h"

//General Log
DEFINE_LOG_CATEGORY(DefaultLog);

//Logging during startup
DEFINE_LOG_CATEGORY(StartupLog);

//Logging for AI 
DEFINE_LOG_CATEGORY(AILog);

//Logging for services
DEFINE_LOG_CATEGORY(ServicesLog);


void UBasicLog::Log(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(DefaultLog, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(StartupLog, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AILog, Log, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(ServicesLog, Log, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogWarning(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(DefaultLog, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(StartupLog, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AILog, Warning, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(ServicesLog, Warning, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogError(FString& message, ELogCategory category)
{
	switch (category)
	{
	default:
		UE_LOG(DefaultLog, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::STARTUP:
		UE_LOG(StartupLog, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::AI:
		UE_LOG(AILog, Error, TEXT("%s"), *message);
		break;
	case ELogCategory::SERVICES:
		UE_LOG(ServicesLog, Error, TEXT("%s"), *message);
		break;
	}
}


void UBasicLog::LogScreenDebug(FString& message, float displayTime)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Turquoise, message);

}

