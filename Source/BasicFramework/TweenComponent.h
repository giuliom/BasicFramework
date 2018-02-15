// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TweenComponent.generated.h"


/**
 * @author Giulio_M
 * 
 * The tween component is responsible for tweening parameters of actors in an asynchronous way but still inside the main game loop
 * It's updated with TickComponent()
 * UTweenComponents are created by TweenFunctionLibrary and they remove themselves when they are done.
 * How the tween affects the actor it's attached to is defined by its TweenMode and enum
 *
*/

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETweenMode : uint8
{
	LINEAR 		UMETA(DisplayName = "Linear"),
	QUADRATIC	UMETA(DisplayName = "Quadratic"),
	EASE_IN		UMETA(DisplayName = "EaseIn"),
	EASE_OUT	UMETA(DisplayName = "EaseOut"),
};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETweenType : uint8
{
	POSITION 	UMETA(DisplayName = "Position"),
	ROTATION	UMETA(DisplayName = "Rotation"),
	TRANSFORM	UMETA(DisplayName = "Transform")
};


DECLARE_DYNAMIC_DELEGATE(FTweenDynamicDelegate);

//TODO check if a template component is possible
UCLASS(BlueprintType, Blueprintable, ClassGroup=(Gameplay), meta=(BlueprintSpawnableComponent) )
class BASICFRAMEWORK_API UTweenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTweenComponent();

protected:

	
	ETweenMode mode = ETweenMode::LINEAR;
	ETweenType type = ETweenType::POSITION;

	// The target actor
	AActor* actor = nullptr;

	// FVectors to be interpolated
	FVector vOrigin = FVector::ZeroVector;
	FVector vTarget = FVector::OneVector;

	// FRotators to be interpolated
	FRotator rOrigin;
	FRotator rTarget;

	// Ftransforms to be interpolated
	FTransform tOrigin;
	FTransform tTarget;

	// Time counter in seconds. Updated with deltime
	float time = 0.0f;

	// The lenght of the animation in seconds
	float targetTime = 1.0f;

	// Should the animation be looping
	bool loop = false;

	// If the the animations works in world or localspace
	bool worldspace = true;

	// The ETeleportType used when setting a location
	ETeleportType tType = ETeleportType::None;

	bool isCompleted = false; 

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitTween(ETweenMode mode, AActor* actor, FVector vOrigin, FVector vTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	void InitTween(ETweenMode mode, AActor* actor, FRotator rOrigin, FRotator rTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	void InitTween(ETweenMode mode, AActor* actor, FTransform tOrigin, FTransform tTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	bool IsTweenCompleted() { return isCompleted; }


protected:

	void BaseInitTween(ETweenMode mode, AActor* actor, float targetTime, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	virtual void BeginPlay() override;

	void TickTween(float alpha);

	void TickPosition(float alpha);

	void TickRotation(float alpha);

	void TickTransform(float alpha);

};
