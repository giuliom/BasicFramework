// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicCharacterMovementComponent.h"

void UBasicCharacterMovementComponent::OnMovementModeChanged(EMovementMode prevMovement, uint8 prevCustomMovement)
{
	Super::OnMovementModeChanged(prevMovement, prevCustomMovement);
}

void UBasicCharacterMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (MovementMode != EMovementMode::MOVE_Custom)
	{
		Super::PhysCustom(deltaTime, Iterations);
	}
	else 
	{
		switch (GetCustomMovementMode())
		{
		case EBasicCharacterCustomMovementMode::CMOVE_LADDER:
			PhysCustomLadder(deltaTime, Iterations);
			break;
		default:
			break;
		}
	}
}

void UBasicCharacterMovementComponent::PhysCustomLadder(float deltaTime, int32 Iterations)
{
	//TODO placeholder
	PhysWalking(deltaTime,Iterations)
}

void UBasicCharacterMovementComponent::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	Super::SetMovementMode(NewMovementMode, NewCustomMode);
	
	if (NewMovementMode == EMovementMode::MOVE_Custom)
	{
		switch (GetCustomMovementMode())
		{
		case EBasicCharacterCustomMovementMode::CMOVE_LADDER:
			break;
		default:
			break;
		}

	}
}
