// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BasicPlayerCameraManager.generated.h"

/**
 * @author Giulio_M
 *
 */
UCLASS()
class BASICFRAMEWORK_API ABasicPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewPitchMin = -89.9f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewPitchMax = 89.9f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewYawMin = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewYawMax = 359.999f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewRollMin = -89.9f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float defViewRollMax = 89.9f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

};
