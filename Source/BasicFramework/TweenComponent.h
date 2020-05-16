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

DECLARE_DYNAMIC_DELEGATE(FTweenDynamicDelegate);

/**
* TweenContainer Class
*/
class TweenContainer
{
protected:
	TweenContainer() {}

public:

	virtual void TickTween(float DeltaTime) {}
	virtual bool isCompleted() const { return true; }
};

/**
* UTweenComponenent Class 
*/
UCLASS(BlueprintType, Blueprintable, ClassGroup = (Gameplay), meta = (BlueprintSpawnableComponent))
class BASICFRAMEWORK_API UTweenComponent : public UActorComponent
{
	GENERATED_BODY()

	TweenContainer* m_tween;

public:

	// Sets default values for this component's properties
	UTweenComponent();

	virtual void BeginDestroy() override;

	void InitContainer(TweenContainer* tween);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsTweenCompleted() const { return m_tween->isCompleted(); }
};


/**
* TweenTemplate Class
*/
template<class T>
class BASICFRAMEWORK_API TweenTemplate
{
protected:

	ETweenMode m_mode = ETweenMode::LINEAR;

	// The lenght of the animation in seconds
	float m_targetTime = 1.0f;

	// Should the animation be looping
	bool m_loop = false;

	// If the the animations works in world or localspace
	bool m_worldspace = true;

	// The ETeleportType used when setting a location
	ETeleportType m_tType = ETeleportType::None;

	// The target actor
	AActor* m_actor = nullptr;

	bool m_isCompleted = false;

	// FVectors to be interpolated
	T m_tOrigin;
	T m_tTarget;

	// Time counter in seconds. Updated with deltime
	float m_time = 0.0f;

public:

	/**
	* Initializes the tween parameters. Every UTweenComponent must be initialized calling an InitTween function
	*
	* @param mode sets the mode of the tween therefore which tweening should execute
	* @param actor the actor that is getting tweened
	* @param vOrigin the initial vector, in this case representing a location
	* @param vTarget the target vector
	* @param targetTime the duration of the tween in seconds
	* @param worldspace if the tween vectors are in worldspace or local.
	* @param loop if the tween must be looping
	* @param teleportPhysics if we must use teleportPhysics when updating the location
*/
	TweenTemplate(ETweenMode mode, AActor* actor, const T& vOrigin, const T& vTarget, float targetTime = 1.0f, bool worldspace = true, bool loop = false, bool teleportPhysics = false)
		: m_mode(mode)
		, m_targetTime(targetTime)
		, m_loop(loop)
		, m_worldspace(worldspace)
		, m_tType(teleportPhysics ? ETeleportType::TeleportPhysics : ETeleportType::None)
		, m_actor(actor)
		, m_isCompleted(false)
		, m_tOrigin(vOrigin)
		, m_tTarget(vTarget)
	{
	}

	void TickTween(float DeltaTime);
	void Apply(float alpha);

	bool isCompleted() const { return m_isCompleted; }
};


/**
* TweenContainer child classes implementing for all the types supported
*/
class TweenLocationContainer : public TweenContainer
{
	TweenTemplate<FVector> m_tween;

public:
	TweenLocationContainer(const TweenTemplate<FVector>& tween) : m_tween(tween)
	{}

	void TickTween(float DeltaTime) override { m_tween.TickTween(DeltaTime); }
	virtual bool isCompleted() const override { return m_tween.isCompleted(); }
};

class TweenRotationContainer : public TweenContainer
{
	TweenTemplate<FRotator> m_tween;

public:
	TweenRotationContainer(const TweenTemplate<FRotator>& tween) : m_tween(tween)
	{}

	void TickTween(float DeltaTime) override { m_tween.TickTween(DeltaTime); }
	virtual bool isCompleted() const override { return m_tween.isCompleted(); }
};

class TweenTransformContainer : public TweenContainer
{
	TweenTemplate<FTransform> m_tween;

public:
	TweenTransformContainer(const TweenTemplate<FTransform>& tween) : m_tween(tween)
	{}

	void TickTween(float DeltaTime) override { m_tween.TickTween(DeltaTime); }
	virtual bool isCompleted() const override { return m_tween.isCompleted(); }
};
