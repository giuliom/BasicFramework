// Fill out your copyright notice in the Description page of Project Settings.

#include "TweenComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UTweenComponent::UTweenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTweenComponent::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}


/**
* Updates the animation in the main game loop.
* If the animation is completed fires the OnTweenCompleted delegate and destroys the component
*/
void UTweenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_time < m_targetTime)
	{
		m_time += DeltaTime;

		TickTween(m_time / m_targetTime);

	}
	else
	{
		if (m_loop)
		{
			m_time = 0;
		}
		else
		{
			TickTween(1.0f);
			m_isCompleted = true;
		}
	}
}

// TODO refactor


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

void UTweenComponent::InitTween(ETweenMode mode, AActor * actor, FVector vOrigin, FVector vTarget, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	this->m_type = ETweenType::POSITION;
	BaseInitTween(mode, actor, targetTime, worldspace, loop, teleportPhysics);
	
	this->m_vOrigin = vOrigin;
	this->m_vTarget = vTarget;
}

void UTweenComponent::InitTween(ETweenMode mode, AActor * actor, FRotator rOrigin, FRotator rTarget, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	this->m_type = ETweenType::ROTATION;
	BaseInitTween(mode, actor, targetTime, worldspace, loop, teleportPhysics);

	this->m_rOrigin = rOrigin;
	this->m_rTarget = rTarget;
}

void UTweenComponent::InitTween(ETweenMode mode, AActor * actor, FTransform tOrigin, FTransform tTarget, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	this->m_type = ETweenType::TRANSFORM;
	BaseInitTween(mode, actor, targetTime, worldspace, loop, teleportPhysics);

	this->m_tOrigin = tOrigin;
	this->m_tTarget = tTarget;
}


void UTweenComponent::BaseInitTween(ETweenMode mode, AActor * actor, float targetTime, bool worldspace, bool loop, bool teleportPhysics)
{
	this->m_mode = mode;
	this->m_actor = actor;
	this->m_targetTime = targetTime;
	this->m_loop = loop;
	this->m_worldspace = worldspace;
	this->m_tType = teleportPhysics ? ETeleportType::TeleportPhysics : ETeleportType::None;
}


void UTweenComponent::TickTween(float alpha)
{
	switch (m_type)
	{
	case ETweenType::POSITION:
		TickPosition(alpha);
		break;

	case ETweenType::ROTATION:
		TickRotation(alpha);
		break;

	case ETweenType::TRANSFORM:
		TickTransform(alpha);
		break;
	}
}


void UTweenComponent::TickPosition(float alpha)
{
	FVector npos = FVector::ZeroVector;

	switch (m_mode)
	{
	default:
		npos = FMath::Lerp<FVector>(m_vOrigin, m_vTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		npos = FMath::InterpExpoIn<FVector>(m_vOrigin, m_vTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		npos = FMath::InterpEaseIn<FVector>(m_vOrigin, m_vTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		npos = FMath::InterpEaseOut<FVector>(m_vOrigin, m_vTarget, alpha, 2);
		break;
	}


	if (m_worldspace) m_actor->SetActorLocation(npos,false, nullptr, m_tType);
	else m_actor->SetActorRelativeLocation(npos, false, nullptr, m_tType);
}


void UTweenComponent::TickRotation(float alpha)
{
	FRotator nrot = FRotator::ZeroRotator;

	switch (m_mode)
	{
	default:
		nrot = FMath::Lerp<FRotator>(m_rOrigin, m_rTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		nrot = FMath::InterpExpoIn<FRotator>(m_rOrigin, m_rTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		nrot = FMath::InterpEaseIn<FRotator>(m_rOrigin, m_rTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		nrot = FMath::InterpEaseOut<FRotator>(m_rOrigin, m_rTarget, alpha, 2);
		break;
	}

	m_actor->SetActorRotation(nrot, m_tType);
}


void UTweenComponent::TickTransform(float alpha)
{
	FVector pos = FVector::ZeroVector;
	FRotator rot = FRotator::ZeroRotator;

	switch (m_mode)
	{
	default:
		pos = FMath::Lerp<FVector>(m_vOrigin, m_vTarget, alpha);
		rot = FMath::Lerp<FRotator>(m_rOrigin, m_rTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		pos = FMath::InterpExpoIn<FVector>(m_vOrigin, m_vTarget, alpha);
		rot = FMath::InterpExpoIn<FRotator>(m_rOrigin, m_rTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		pos = FMath::InterpEaseIn<FVector>(m_vOrigin, m_vTarget, alpha, 2);
		rot = FMath::InterpEaseIn<FRotator>(m_rOrigin, m_rTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		pos = FMath::InterpEaseOut<FVector>(m_vOrigin, m_vTarget, alpha, 2);
		rot = FMath::InterpEaseOut<FRotator>(m_rOrigin, m_rTarget, alpha, 2);
		break;
	}

	m_actor->SetActorTransform(FTransform(rot, pos), false, nullptr, m_tType);
}



