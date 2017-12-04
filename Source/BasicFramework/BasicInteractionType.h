// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractionType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EBasicInteractionType : uint8
{
	DEFAULT 	UMETA(DisplayName = "Default"),
	SECONDARY	UMETA(DisplayName = "Secondary"),
	THIRD		UMETA(DisplayName = "Third"),
	FOURTH		UMETA(DisplayName = "Fourth")
};

