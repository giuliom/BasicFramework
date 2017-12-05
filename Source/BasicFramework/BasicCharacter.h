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
		virtual void OnPossessInternal_Implementation(int32 index) override;

	// Called by BasicPlayerController before possessing another character. BlueprintNativeEvent
		virtual void OnUnpossessInternal_Implementation() override;


	//----------------------- MOVEMENT METHODS -----------------------

	virtual void Jump() override;

	virtual void StopJumping() override;
	

	//----------------------- INPUT PROCESSING METHODS -----------------------
	
	virtual void ProcessInputForwardInternal_Implementation(float val) override;
	virtual void ProcessInputRightInternal_Implementation(float val) override;

	virtual void ProcessInputButtonAInternal_Implementation() override;
	virtual void ProcessInputButtonA_ReleasedInternal_Implementation() override;

	virtual void ProcessInputButtonBInternal_Implementation() override;
	virtual void ProcessInputButtonB_ReleasedInternal_Implementation() override;

	virtual void ProcessInputButtonXInternal_Implementation() override;
	virtual void ProcessInputButtonX_ReleasedInternal_Implementation() override;

	virtual void ProcessInputButtonYInternal_Implementation() override;
	virtual void ProcessInputButtonY_ReleasedInternal_Implementation() override;

	virtual void ProcessInputLeftBumperInternal_Implementation() override;
	virtual void ProcessInputLeftBumper_ReleasedInternal_Implementation() override;

	virtual void ProcessInputRightBumperInternal_Implementation() override;
	virtual void ProcessInputRightBumper_ReleasedInternal_Implementation() override;

	virtual void ProcessInputStartInternal_Implementation() override;
	virtual void ProcessInputStart_ReleasedInternal_Implementation() override;

	virtual void ProcessInputBackInternal_Implementation() override;
	virtual void ProcessInputBack_ReleasedInternal_Implementation() override;

	virtual void ProcessInputLeftTriggerInternal_Implementation(float val) override;
	virtual void ProcessInputRightTriggerInternal_Implementation(float val) override;

	virtual void ProcessInputRotateRightInternal_Implementation(float val) override; //Yaw
	virtual void ProcessInputRotateUpInternal_Implementation(float val) override; //Pitch

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputTurnAtRateInternal_Implementation(float val) override;

	/**
	* @param Rate	This is a normalized rate, 1.0 means full rate
	*/
	virtual void ProcessInputLookUpAtRateInternal_Implementation(float val) override;

};
