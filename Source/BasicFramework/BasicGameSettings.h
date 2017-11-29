// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
//#include "Runtime/Core/Public/GenericPlatform/GenericWindow.h"
#include "BasicGameSettings.generated.h"

/**
* @author Giulio_M
*
* This class stores all the settings data
*/
UCLASS()
class BASICFRAMEWORK_API UBasicGameSettings : public USaveGame
{
	GENERATED_BODY()


public:
	
	uint32 bloom = 1;

	int32 screenWidth = 1920;
	int32 screenHeight = 1080;
	
	//EWindowMode::Type windowMode = EWindowMode::Type::Fullscreen;

	bool invertYAxis = false;


};
