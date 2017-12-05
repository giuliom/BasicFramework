// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/Interface.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "BasicPawnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class BASICFRAMEWORK_API UBasicPawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @author Giulio_M
 *
 * Interface providing common methods to any actor that must receive input
 */
class BASICFRAMEWORK_API IBasicPawnInterface
{
	GENERATED_BODY()

protected:
	int32 playerIndex = 0;

	bool bMovementEnabled = true;
	bool bRotationEnabled = true;

	FGameplayTag gameplayTag;

public:

	virtual int32 GetPlayerIndex();
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnPossess(int32 index) { OnPossessInternal(index); }
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void OnUnpossess() { OnUnpossessInternal(); }
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	bool IsMovementEnabled() const { return IsMovementEnabledInternal(); }
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void SetMovementEnabled(bool val) { SetMovementEnabledInternal(val); }
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	bool IsRotationEnabled() const { return IsRotationEnabledInternal(); }
	
	UFUNCTION(BlueprintCallable, Category = "Pawn")
	void SetRotationEnabled(bool val) { SetRotationEnabledInternal(val); }

	//UFUNCTION(BlueprintCallable)
	FGameplayTag GetGameplayTag() const { return gameplayTag; }

	//UFUNCTION(BlueprintCallable)
	void SetGameplayTag(FGameplayTag t) { gameplayTag = t; }


protected:

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "OnPossess"))
	void OnPossessInternal(int32 index);
	virtual void OnPossessInternal_Implementation(int32 index) { playerIndex = index; };

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "OnUnpossess"))
	void OnUnpossessInternal();
	virtual void OnUnpossessInternal_Implementation() {}

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "IsMovementEnabled"))
	bool IsMovementEnabledInternal() const;
	virtual bool IsMovementEnabledInternal_Implementation() const { return bMovementEnabled; }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "SetMovementEnabled"))
	void SetMovementEnabledInternal(bool val);
	virtual void SetMovementEnabledInternal_Implementation(bool val) { bMovementEnabled = val; }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "IsRotationEnabled"))
	bool IsRotationEnabledInternal() const;
	virtual bool IsRotationEnabledInternal_Implementation() const { return bRotationEnabled; }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "SetRotationEnabled"))
	void SetRotationEnabledInternal(bool val);
	virtual void SetRotationEnabledInternal_Implementation(bool val) { bRotationEnabled = val; }

	//----------------------- INPUT PROCESSING METHODS -----------------------

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputForward(float val) { ProcessInputForwardInternal(val); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRight(float val) { ProcessInputRightInternal(val); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonA() { ProcessInputButtonAInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonA_Released() { ProcessInputButtonA_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonB() { ProcessInputButtonBInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonB_Released() { ProcessInputButtonB_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonX() { ProcessInputButtonXInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonX_Released() { ProcessInputButtonX_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonY() { ProcessInputButtonYInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputButtonY_Released() { ProcessInputButtonY_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputLeftBumper() { ProcessInputLeftBumperInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputLeftBumper_Released() { ProcessInputLeftBumper_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRightBumper() { ProcessInputRightBumperInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRightBumper_Released() { ProcessInputRightBumper_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputStart() { ProcessInputStartInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputStart_Released() { ProcessInputStart_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputBack() { ProcessInputBackInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputBack_Released() { ProcessInputBack_ReleasedInternal(); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputLeftTrigger(float val) { ProcessInputLeftTriggerInternal(val); }

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRightTrigger(float val) { ProcessInputRightTriggerInternal(val); }

	//Yaw
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRotateRight(float val) { ProcessInputRotateRightInternal(val); }

	//Pitch
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputRotateUp(float val) { ProcessInputRotateUpInternal(val); }

	/** @param Rate	This is a normalized rate, 1.0 means full rate */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputTurnAtRate(float val) { ProcessInputTurnAtRateInternal(val); }

	/** @param Rate	This is a normalized rate, 1.0 means full rate */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ProcessInputLookUpAtRate(float val) { ProcessInputLookUpAtRateInternal(val); }

protected:

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputForward"))
	void ProcessInputForwardInternal(float val);
	virtual void ProcessInputForwardInternal_Implementation(float val) {  }
	
	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRight"))
	void ProcessInputRightInternal(float val);
	virtual void ProcessInputRightInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonA"))
	void ProcessInputButtonAInternal();
	virtual void ProcessInputButtonAInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonA_Released"))
	void ProcessInputButtonA_ReleasedInternal();
	virtual void ProcessInputButtonA_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonB"))
	void ProcessInputButtonBInternal();
	virtual void ProcessInputButtonBInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonB_Released"))
	void ProcessInputButtonB_ReleasedInternal();
	virtual void ProcessInputButtonB_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonX"))
	void ProcessInputButtonXInternal();
	virtual void ProcessInputButtonXInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonX_Released"))
	void ProcessInputButtonX_ReleasedInternal();
	virtual void ProcessInputButtonX_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonY"))
	void ProcessInputButtonYInternal();
	virtual void ProcessInputButtonYInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputButtonY_Released"))
	void ProcessInputButtonY_ReleasedInternal();
	virtual void ProcessInputButtonY_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputLeftBumper"))
	void ProcessInputLeftBumperInternal();
	virtual void ProcessInputLeftBumperInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputLeftBumper_Released"))
	void ProcessInputLeftBumper_ReleasedInternal();
	virtual void ProcessInputLeftBumper_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRightBumper"))
	void ProcessInputRightBumperInternal();
	virtual void ProcessInputRightBumperInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRightBumper_Released"))
	void ProcessInputRightBumper_ReleasedInternal();
	virtual void ProcessInputRightBumper_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputStart"))
	void ProcessInputStartInternal();
	virtual void ProcessInputStartInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputStart_Released"))
	void ProcessInputStart_ReleasedInternal();
	virtual void ProcessInputStart_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputBack"))
	void ProcessInputBackInternal();
	virtual void ProcessInputBackInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputBack_Released"))
	void ProcessInputBack_ReleasedInternal();
	virtual void ProcessInputBack_ReleasedInternal_Implementation() {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputLeftTrigger"))
	void ProcessInputLeftTriggerInternal(float val);
	virtual void ProcessInputLeftTriggerInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRightTrigger"))
	void ProcessInputRightTriggerInternal(float val);
	virtual void ProcessInputRightTriggerInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRotateRight"))
	void ProcessInputRotateRightInternal(float val);
	virtual void ProcessInputRotateRightInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputRotateUp"))
	void ProcessInputRotateUpInternal(float val);
	virtual void ProcessInputRotateUpInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputTurnAtRate"))
	void ProcessInputTurnAtRateInternal(float val);
	virtual void ProcessInputTurnAtRateInternal_Implementation(float val) {  }

	UFUNCTION(BlueprintNativeEvent, Category = Input, meta = (DisplayName = "ProcessInputLookUpAtRate"))
	void ProcessInputLookUpAtRateInternal(float val);
	virtual void ProcessInputLookUpAtRateInternal_Implementation(float val) {  }
};
