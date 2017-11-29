// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicGameSettings.h"
#include "Engine/RendererSettings.h"
#include "GameFramework/GameUserSettings.h"


/**
 * @author Giulio_M
 *
 * This class manages the settings set in the options menu of the game, including rendering settings.
 * All the settings data is stored in the class UGameSettings
*/
class BASICFRAMEWORK_API SettingsManager
{
public:
	
	FString playerName;
	FString saveSlotName;
	uint32 userIndex;

	//Stores the actual settings data
	UBasicGameSettings* uSettings = nullptr;

protected:
	URendererSettings* rSettings = nullptr;
	UGameUserSettings* gSettings = nullptr;

public:
	SettingsManager(FString playerName, FString saveSlotName, uint32 userIndex);
	~SettingsManager();

	void LoadSettings();
	void ApplySettings();
	void SaveSettings();

	//void SetScreenResolution(int32 width, int32 height, EWindowMode::Type wMode);

protected:

	UGameUserSettings* GetGameUserSettings() const;
};
