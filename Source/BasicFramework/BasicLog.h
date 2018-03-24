// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BasicLog.generated.h"

/**
* @author Giulio_M
*
* This class provides a simple to use logging library for C++ and blueprints
* Define new categories using the macros in this file and BasicLog.cpp and expanding the enum
* ELogCategory and related functions.
*/

//General Log
DECLARE_LOG_CATEGORY_EXTERN(DefaultLog, Log, All);

//Logging during startup
DECLARE_LOG_CATEGORY_EXTERN(StartupLog, Log, All);

//Logging for AI 
DECLARE_LOG_CATEGORY_EXTERN(AILog, Log, All);

//Logging for services
DECLARE_LOG_CATEGORY_EXTERN(ServicesLog, Log, All);


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ELogCategory : uint8
{
	DEFAULT		UMETA(DisplayName = "Default"),
	STARTUP		UMETA(DisplayName = "Startup"),
	AI			UMETA(DisplayName = "AI"),
	SERVICES	UMETA(DisplayName = "Services"),
};


UCLASS()
class BASICFRAMEWORK_API UBasicLog : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Log")
	static void Log(FString& message, ELogCategory category = ELogCategory::DEFAULT);
	
	UFUNCTION(BlueprintCallable, Category = "Log")
	static void LogWarning(FString& message, ELogCategory category = ELogCategory::DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "Log")
	static void LogError(FString& message, ELogCategory category = ELogCategory::DEFAULT);

	UFUNCTION(BlueprintCallable, Category = "Log")
	static void LogScreenDebug(FString& message, float displayTime = 2.0f);

	//TODO DrawDebug extended functionalities
};
