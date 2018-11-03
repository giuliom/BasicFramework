// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicInteractionTypeFactory.h"
#include "BasicInteractionType.h"


UBasicInteractionTypeFactory::UBasicInteractionTypeFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UBasicInteractionType::StaticClass();
}

UObject * UBasicInteractionTypeFactory::FactoryCreateNew(UClass * Class, UObject * InParent, FName Name, EObjectFlags Flags, UObject * Context, FFeedbackContext * Warn)
{
	UBasicInteractionType* newType = NewObject<UBasicInteractionType>(InParent, Class, Name, Flags | RF_Transactional);
	newType->Name = "InteractionType";
	return newType;
}
