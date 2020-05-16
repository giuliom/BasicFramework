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

void UTweenComponent::BeginDestroy()
{
	Super::BeginDestroy();

	delete m_tween;
}

void UTweenComponent::InitContainer(TweenContainer* tween)
{
	m_tween =tween;
}

/**
* Updates the animation in the main game loop.
* If the animation is completed fires the OnTweenCompleted delegate and destroys the component
*/
void UTweenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_tween->TickTween(DeltaTime);
}

template<class T>
void TweenTemplate<T>::TickTween(float DeltaTime)
{
	if (m_time < m_targetTime)
	{
		m_time += DeltaTime;

		Apply(m_time / m_targetTime);

	}
	else
	{
		if (m_loop)
		{
			m_time = 0;
		}
		else
		{
			Apply(1.0f);
			m_isCompleted = true;
		}
	}
}


template<>
void TweenTemplate<FVector>::Apply(float alpha)
{
	FVector npos = FVector::ZeroVector;
	TArray<int> array;
	switch (m_mode)
	{
	default:
		npos = FMath::Lerp<FVector>(m_tOrigin, m_tTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		npos = FMath::InterpExpoIn<FVector>(m_tOrigin, m_tTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		npos = FMath::InterpEaseIn<FVector>(m_tOrigin, m_tTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		npos = FMath::InterpEaseOut<FVector>(m_tOrigin, m_tTarget, alpha, 2);
		break;
	}


	if (m_worldspace) m_actor->SetActorLocation(npos, false, nullptr, m_tType);
	else m_actor->SetActorRelativeLocation(npos, false, nullptr, m_tType);
}

template<>
void TweenTemplate<FRotator>::Apply(float alpha)
{
	FRotator nrot = FRotator::ZeroRotator;

	switch (m_mode)
	{
	default:
		nrot = FMath::Lerp<FRotator>(m_tOrigin, m_tTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		nrot = FMath::InterpExpoIn<FRotator>(m_tOrigin, m_tTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		nrot = FMath::InterpEaseIn<FRotator>(m_tOrigin, m_tTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		nrot = FMath::InterpEaseOut<FRotator>(m_tOrigin, m_tTarget, alpha, 2);
		break;
	}

	if (m_worldspace) m_actor->SetActorRotation(nrot, m_tType);
	else m_actor->SetActorRelativeRotation(nrot, false, nullptr, m_tType);
}

template<>
void TweenTemplate<FTransform>::Apply(float alpha)
{
	FVector pos = FVector::ZeroVector;
	FVector scale = FVector::OneVector;
	FRotator rot = FRotator::ZeroRotator;

	const FVector vOrigin = m_tOrigin.GetLocation();
	const FVector vTarget = m_tTarget.GetLocation();

	const FVector sOrigin = m_tOrigin.GetScale3D();
	const FVector sTarget = m_tOrigin.GetScale3D();

	const FRotator rOrigin = m_tOrigin.GetRotation().Rotator();
	const FRotator rTarget = m_tTarget.GetRotation().Rotator();

	switch (m_mode)
	{
	default:
		pos		= FMath::Lerp<FVector>(vOrigin, vTarget, alpha);
		scale	= FMath::Lerp<FVector>(sOrigin, sTarget, alpha);
		rot		= FMath::Lerp<FRotator>(rOrigin, rTarget, alpha);
		break;

	case ETweenMode::QUADRATIC:
		pos		= FMath::InterpExpoIn<FVector>(vOrigin, vTarget, alpha);
		scale	= FMath::InterpExpoIn<FVector>(sOrigin, sTarget, alpha);
		rot		= FMath::InterpExpoIn<FRotator>(rOrigin, rTarget, alpha);
		break;

	case ETweenMode::EASE_IN:
		pos		= FMath::InterpEaseIn<FVector>(vOrigin, vTarget, alpha, 2);
		scale	= FMath::InterpEaseIn<FVector>(sOrigin, sTarget, alpha, 2);
		rot		= FMath::InterpEaseIn<FRotator>(rOrigin, rTarget, alpha, 2);
		break;

	case ETweenMode::EASE_OUT:
		pos		= FMath::InterpEaseOut<FVector>(vOrigin, vTarget, alpha, 2);
		scale	= FMath::InterpEaseOut<FVector>(sOrigin, sTarget, alpha, 2);
		rot		= FMath::InterpEaseOut<FRotator>(rOrigin, rTarget, alpha, 2);
		break;
	}

	FTransform t(rot, pos, scale);

	if (m_worldspace) m_actor->SetActorTransform(t, false, nullptr, m_tType);
	else m_actor->SetActorRelativeTransform(t, false, nullptr, m_tType);
}



