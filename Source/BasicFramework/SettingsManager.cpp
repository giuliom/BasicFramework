// Fill out your copyright notice in the Description page of Project Settings.

#include "SettingsManager.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"


SettingsManager::SettingsManager(FString playerName, FString saveSlotName, uint32 userIndex)
{
	this->playerName = playerName;
	this->saveSlotName = saveSlotName;
	this->userIndex = userIndex;

	gSettings = GetGameUserSettings();

	LoadSettings();
}


SettingsManager::~SettingsManager()
{

}


void SettingsManager::LoadSettings()
{
	uSettings = Cast<UBasicGameSettings>(UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex));

	if (uSettings == nullptr) uSettings = Cast<UBasicGameSettings>(UGameplayStatics::CreateSaveGameObject(UBasicGameSettings::StaticClass()));

	ApplySettings();
}



void SettingsManager::ApplySettings()
{
//	SetScreenResolution(uSettings->screenWidth, uSettings->screenHeight, uSettings->windowMode);

	gSettings->ConfirmVideoMode();

	gSettings->ApplySettings(false); //Also saves to storage
									 //gSettings->SaveSettings();

	SaveSettings();
}


void SettingsManager::SaveSettings()
{
	if (uSettings != nullptr) UGameplayStatics::SaveGameToSlot((USaveGame*) uSettings, saveSlotName, userIndex);
}

/*
void SettingsManager::SetScreenResolution(int32 width, int32 height, EWindowMode::Type wMode)
{
	gSettings->RequestResolutionChange(width, height, wMode, false);

	//To save the settings
	gSettings->SetScreenResolution(FIntPoint(width, height));
	gSettings->SetFullscreenMode(wMode);
}
*/

UGameUserSettings* SettingsManager::GetGameUserSettings() const
{
	if (GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}
	return nullptr;
}

