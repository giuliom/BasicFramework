// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CollisionQueryParams.h"
#include "Runtime/Engine/Public/EngineUtils.h"
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

	UFUNCTION(BlueprintCallable, Category = "Basic Utils")
	static AActor* FindActorByName(FString name);
	
	/** ATTENTION: the method is slow */
	UFUNCTION(BlueprintCallable, Category = "Basic Utils")
	static TArray<AActor*> FindActorsByTag(UWorld* world, FName tag);

	UFUNCTION(BlueprintCallable, Category = "Basic Utils")
	static UActorComponent* LineTraceComponent(FHitResult& outHit, AActor* actor, UClass* componentClass, const FVector& start, const FVector& end, ECollisionChannel channel = ECollisionChannel::ECC_GameTraceChannel1, bool ignoreActor = true);
};
