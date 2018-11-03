// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BasicInteractionTypeFactory.generated.h"

/**
 * 
 */
UCLASS()
class BASICFRAMEWORK_API UBasicInteractionTypeFactory : public UFactory
{
	GENERATED_BODY()

public:
	UBasicInteractionTypeFactory(const FObjectInitializer& ObjectInitializer);
	
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;	
};
