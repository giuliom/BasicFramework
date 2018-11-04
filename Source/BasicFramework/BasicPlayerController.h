// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicCharacter.h"
#include "BasicPlayerCameraManager.h"
#include "BasicPlayerController.generated.h"

/**
 * @author @Giulio_M
 * 
 * Default Player Controller class
 * It can possess class DefaultCharacter and derivateed classes.
 * **ALWAYS USE** PossessCharacter() do posses one.
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInputAction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputAxis, float, value);

UCLASS()
class BASICFRAMEWORK_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	ABasicPlayerCameraManager* cameraManager = nullptr;

protected:

	IBasicPawnInterface* characterPawnInterface = nullptr;


	// Buttons-Actions binding values
	FString buttonA = "ButtonA";
	FString buttonB = "ButtonB";
	FString buttonX = "ButtonX";
	FString buttonY = "ButtonY";
	FString buttonLB = "ButtonLB";
	FString buttonRB = "ButtonRB";
	FString buttonStart = "ButtonStart";
	FString buttonBack = "ButtonBack";
	FString leftTrigger = "LeftTrigger";
	FString rightTrigger = "RightTrigger";

	UPROPERTY(BlueprintReadOnly, Category = Camera)
		float minCameraRotationYaw = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
		float maxCameraRotationYaw = 359.99f;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
		float minCameraRotationPitch = -89.9f;

	UPROPERTY(BlueprintReadOnly, Category = Camera)
		float maxCameraRotationPitch = 89.9f;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Setups input gameplay bindings
	virtual void SetupInputComponent() override;

	void ResetInputDelegates();

public:

	ABasicPlayerController();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
		void PossessBasicPawn(APawn* pCharacter);


	/** ----------------------------- INPUT PROCESSING -------------------------------*/

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonA();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonA_Released();

	FInputAction delInputButtonA_Pressed;
	FInputAction delInputButtonA_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonB();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonB_Released();

	FInputAction delInputButtonB_Pressed;
	FInputAction delInputButtonB_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonX();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonX_Released();

	FInputAction delInputButtonX_Pressed;
	FInputAction delInputButtonX_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonY();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputButtonY_Released();

	FInputAction delInputButtonY_Pressed;
	FInputAction delInputButtonY_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputLeftBumper();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputLeftBumper_Released();

	FInputAction delInputLeftBumper_Pressed;
	FInputAction delInputLeftBumper_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputRightBumper();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputRightBumper_Released();

	FInputAction delInputRightBumper_Pressed;
	FInputAction delInputRightBumper_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputStart();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputStart_Released();

	FInputAction delInputStart_Pressed;
	FInputAction delInputStart_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputBack();

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputBack_Released();

	FInputAction delInputBack_Pressed;
	FInputAction delInputBack_Released;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputLeftTrigger(float Val);

	FInputAxis delInputLeftTrigger;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputRightTrigger(float Val);

	FInputAxis delInputRightTrigger;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputForward(float Val);

	FInputAxis delInputForward;

	UFUNCTION(BlueprintCallable, Category = Input)
		virtual void ProcessInputRight(float Val);

	FInputAxis delInputRight;

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputTurnAtRate(float rate);

	FInputAxis delInputTurnAtRate;

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputLookUpAtRate(float rate);

	FInputAxis delInputLookUpAtRate;

	virtual void ProcessInputRotateRight(float val);

	FInputAxis delInputRotateRight;

	virtual void ProcessInputRotateUp(float val);

	FInputAxis delInputRotateUp;


};
