// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayerCameraManager.h"

void ABasicPlayerCameraManager::BeginPlay()
{
	ViewPitchMin = defViewPitchMin;
	ViewPitchMax = defViewPitchMax;
	ViewYawMin = defViewYawMin;
	ViewYawMax = defViewYawMax;
	ViewRollMin = defViewRollMin;
	ViewRollMax = defViewRollMax;

	Super::BeginPlay();
}


