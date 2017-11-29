// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BasicUtils.generated.h"


/**
 * @author Giulio_M
 *
 * Function Library providing useful methods for Blueprints and C++
 */
UCLASS()
class BASICFRAMEWORK_API UBasicUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	* Disable or enable the actors and all its components 
	*/
	UFUNCTION(BlueprintCallable, Category = "Basic Utils")
		static void SetActorEnabled(AActor* actor, bool enabled);


};
