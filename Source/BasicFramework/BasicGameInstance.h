// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "BasicGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BASICFRAMEWORK_API UBasicGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	FName levelToLoad = "";
	FName lastStreamedLevel = "";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UserInterface")
	TSubclassOf<class UUserWidget> loadingWidgetClass = nullptr;

	UUserWidget* loadingWidget = nullptr;
	
public:

	virtual void Init() override;

	UFUNCTION()
	virtual void ShowLoadingScreen(const FString& levelName);
	UFUNCTION()
	virtual void HideLoadingScreen();
	
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	FName GetLevelToLoad() const { return levelToLoad; }
	
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	FName GetLastStreamedLevel() const { return lastStreamedLevel; }
	
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void SetLevelToLoad(FName nlevel) { levelToLoad = nlevel; }
	
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void SetLastStreamedLevel(FName level) { lastStreamedLevel = level; }

};
