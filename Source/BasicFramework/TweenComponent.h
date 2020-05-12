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

	
	ETweenMode m_mode = ETweenMode::LINEAR;
	ETweenType m_type = ETweenType::POSITION;

	// The target actor
	AActor* m_actor = nullptr;

	// FVectors to be interpolated
	FVector m_vOrigin = FVector::ZeroVector;
	FVector m_vTarget = FVector::OneVector;

	// FRotators to be interpolated
	FRotator m_rOrigin;
	FRotator m_rTarget;

	// Ftransforms to be interpolated
	FTransform m_tOrigin;
	FTransform m_tTarget;

	// Time counter in seconds. Updated with deltime
	float m_time = 0.0f;

	// The lenght of the animation in seconds
	float m_targetTime = 1.0f;

	// Should the animation be looping
	bool m_loop = false;

	// If the the animations works in world or localspace
	bool m_worldspace = true;

	// The ETeleportType used when setting a location
	ETeleportType m_tType = ETeleportType::None;

	bool m_isCompleted = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitTween(ETweenMode mode, AActor* actor, FVector vOrigin, FVector vTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	void InitTween(ETweenMode mode, AActor* actor, FRotator rOrigin, FRotator rTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	void InitTween(ETweenMode mode, AActor* actor, FTransform tOrigin, FTransform tTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	bool IsTweenCompleted() { return m_isCompleted; }


protected:

	void BaseInitTween(ETweenMode mode, AActor* actor, float targetTime, bool worldspace = true, bool loop = false, bool teleportPhysics = false);

	virtual void BeginPlay() override;

	void TickTween(float alpha);

	void TickPosition(float alpha);

	void TickRotation(float alpha);

	void TickTransform(float alpha);

};
