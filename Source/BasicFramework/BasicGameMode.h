// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Camera/CameraComponent.h"
#include "BasicCharacter.h"
#include "BasicPlayerController.h"
#include "SettingsManager.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "BasicGameMode.generated.h"

/**
*
*/
UCLASS()
class BASICFRAMEWORK_API ABasicGameMode : public AGameModeBase
{
	GENERATED_BODY()


protected:
	
		//Handles the game, rendering etc.. settings
		SettingsManager* settings = nullptr;

		//Name of the player that owns the current saves
		FString playerName = "player1";

		//Name of the settings slow
		FString saveSlotSettings = "test_settings";

		//Current user index used for saving and input management
		uint32 userIndex = 0;

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

		bool bGamePaused = false;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserInterface")
		TSubclassOf<class UUserWidget> pauseWidgetClass = nullptr;

		UUserWidget* pauseWidget = nullptr;

public:

		/** Initialize the game. Called before any other function including PreInitializeComponents()
		@param MapName
		@param Options
		@param ErrorMessage
		*/
		virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

		UFUNCTION(BlueprintCallable)
		bool IsGamePaused() const;

		UFUNCTION(BlueprintCallable)
		virtual void SetGamePaused(bool val);

		UFUNCTION(BlueprintCallable, BlueprintPure)
		ABasicCharacter* GetDefaultCharacter() const;

		UFUNCTION(BlueprintCallable, BlueprintPure)
		ABasicPlayerController* GetDefaultPlayerController() const;

};
