// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BasicInteractionType.h"
#include "BasicPawnInterface.h"
#include "BasicInteractionComponent.h"
#include "BasicCharacter.generated.h"


/**
* @author Giulio_M
* Basic Character class for first person adventure games
*
*/
UCLASS(Blueprintable)
class BASICFRAMEWORK_API ABasicCharacter : public ACharacter, public IBasicPawnInterface
{
	GENERATED_BODY()

protected:
	
	bool bCanJump = true;
	bool bCanRun = true;
	bool bIsWalking = false;
	bool bIsRunning = false;
	bool bIsJumping = false;

	UCharacterMovementComponent* movementComponent = nullptr;

	float maxSpeedCached = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
		FName cameraSocket = "head";

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate = 30.0f;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
		float runningSpeedMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float defaultRaycastDistance = 200.f;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float turnRateMultiplier = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float lookUpRateMultiplier = 30.0f;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this character's properties
	ABasicCharacter(const FObjectInitializer & ObjectInitializer);

	/** First person camera TODO: move to protected */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* firstPersonCameraComponent;

	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return firstPersonCameraComponent; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsWalking() const { return bIsWalking; }

	UFUNCTION(BlueprintCallable)
		void SetCanJump(bool val) { bCanJump = val; }

	UFUNCTION(BlueprintCallable)
		void SetCanRun(bool val) { bCanRun = val; }

	UFUNCTION(BlueprintCallable)
		FORCEINLINE bool IsRunning() const { return bIsRunning; }

	UFUNCTION(BlueprintCallable)
		void SetRunning(bool val);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		EMovementMode GetMovementMode() const { return GetCharacterMovement()->MovementMode.GetValue(); }

	UFUNCTION(BlueprintCallable)
		virtual void SetSwimming(bool enabled);


	//----------------------- GAMEPLAY METHODS -----------------------

	// Used to interacts with objects that implement InteractiveInterface by calling their Execute() method
	UFUNCTION(BlueprintCallable)
		virtual bool Interact(EBasicInteractionType iType = EBasicInteractionType::DEFAULT);

	// Called by BasicPlayerController after possessing the character. BlueprintNativeEvent
		virtual void OnPossess_Internal(int32 index) override;

	// Called by BasicPlayerController before possessing another character. BlueprintNativeEvent
		virtual void OnUnpossess_Internal() override;


	//----------------------- MOVEMENT METHODS -----------------------

	virtual void Jump() override;

	virtual void StopJumping() override;
	

	//----------------------- INPUT PROCESSING METHODS -----------------------
	
	virtual void ProcessInputForward_Internal(float val) override;
	virtual void ProcessInputRight_Internal(float val) override;

	virtual void ProcessInputButtonA_Internal() override;
	virtual void ProcessInputButtonA_Released_Internal() override;

	virtual void ProcessInputButtonB_Internal() override;
	virtual void ProcessInputButtonB_Released_Internal() override;

	virtual void ProcessInputButtonX_Internal() override;
	virtual void ProcessInputButtonX_Released_Internal() override;

	virtual void ProcessInputButtonY_Internal() override;
	virtual void ProcessInputButtonY_Released_Internal() override;

	virtual void ProcessInputLeftBumper_Internal() override;
	virtual void ProcessInputLeftBumper_Released_Internal() override;

	virtual void ProcessInputRightBumper_Internal() override;
	virtual void ProcessInputRightBumper_Released_Internal() override;

	virtual void ProcessInputStart_Internal() override;
	virtual void ProcessInputStart_Released_Internal() override;

	virtual void ProcessInputBack_Internal() override;
	virtual void ProcessInputBack_Released_Internal() override;

	virtual void ProcessInputLeftTrigger_Internal(float val) override;
	virtual void ProcessInputRightTrigger_Internal(float val) override;

	virtual void ProcessInputRotateRight_Internal(float val) override; //Yaw
	virtual void ProcessInputRotateUp_Internal(float val) override; //Pitch

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputTurnAtRate_Internal(float val) override;

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputLookUpAtRate_Internal(float val) override;

};
