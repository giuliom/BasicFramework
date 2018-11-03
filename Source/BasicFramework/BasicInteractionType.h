// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractionType.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class UBasicInteractionType : public UObject
{
	GENERATED_BODY()
 
public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UBasicInteractionType(const FObjectInitializer& ObjectInitializer);
};
