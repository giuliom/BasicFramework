// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/CoreUObject/Public/UObject/Interface.h"
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
 */
class BASICFRAMEWORK_API IBasicPawnInterface
{
	GENERATED_BODY()

protected:
	int32 playerIndex = 0;

	bool bMovementEnabled = true;
	bool bRotationEnabled = true;

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void OnPossess(int32 index);
	void OnPossess_Implementation(int32 index) { OnPossess_Internal(index); }
	virtual void OnPossess_Internal(int32 index) { playerIndex = index; };
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void OnDispossess();
	void OnDispossess_Implementation() { OnDispossess_Internal(); }
	virtual void OnDispossess_Internal() {}

	virtual int32 GetPlayerIndex();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pawn)
	bool IsMovementEnabled() const;
	bool IsMovementEnabled_Implementation() const { return IsMovementEnabled_Internal(); }
	virtual bool IsMovementEnabled_Internal() const { return bMovementEnabled; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pawn)
	void SetMovementEnabled(bool val);
	void SetMovementEnabled_Implementation(bool val) { SetMovementEnabled_Internal(val); }
	virtual void SetMovementEnabled_Internal(bool val) { bMovementEnabled = val; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pawn)
	bool IsRotationEnabled() const;
	bool IsRotationEnabled_Implementation() const { return IsRotationEnabled_Internal(); }
	virtual bool IsRotationEnabled_Internal() const { return bRotationEnabled; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Pawn)
	void SetRotationEnabled(bool val);
	void SetRotationEnabled_Implementation(bool val) { SetRotationEnabled_Internal(val); }
	virtual void SetRotationEnabled_Internal(bool val) { bRotationEnabled = val; }



	//----------------------- INPUT PROCESSING METHODS -----------------------
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputForward(float val);
	void ProcessInputForward_Implementation(float val) { ProcessInputForward_Internal(val); }
	virtual void ProcessInputForward_Internal(float val) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRight(float val);
	void ProcessInputRight_Implementation(float val) { ProcessInputRight_Internal(val); }
	virtual void ProcessInputRight_Internal(float val) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonA();
	void ProcessInputButtonA_Implementation() { ProcessInputButtonA_Internal(); }
	virtual void ProcessInputButtonA_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonA_Released();
	void ProcessInputButtonA_Released_Implementation() { ProcessInputButtonA_Released_Internal(); }
	virtual void ProcessInputButtonA_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonB();
	void ProcessInputButtonB_Implementation() { ProcessInputButtonB_Internal(); }
	virtual void ProcessInputButtonB_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonB_Released();
	void ProcessInputButtonB_Released_Implementation() { ProcessInputButtonB_Released_Internal(); }
	virtual void ProcessInputButtonB_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonX();
	void ProcessInputButtonX_Implementation() { ProcessInputButtonX_Internal(); }
	virtual void ProcessInputButtonX_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonX_Released();
	void ProcessInputButtonX_Released_Implementation() { ProcessInputButtonX_Released_Internal(); }
	virtual void ProcessInputButtonX_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonY();
	void ProcessInputButtonY_Implementation() { ProcessInputButtonY_Internal(); }
	virtual void ProcessInputButtonY_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputButtonY_Released();
	void ProcessInputButtonY_Released_Implementation() { ProcessInputButtonY_Released_Internal(); }
	virtual void ProcessInputButtonY_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputLeftBumper();
	void ProcessInputLeftBumper_Implementation() { ProcessInputLeftBumper_Internal(); }
	virtual void ProcessInputLeftBumper_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputLeftBumper_Released();
	void ProcessInputLeftBumper_Released_Implementation() { ProcessInputLeftBumper_Released_Internal(); }
	virtual void ProcessInputLeftBumper_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRightBumper();
	void ProcessInputRightBumper_Implementation() { ProcessInputRightBumper_Internal(); }
	virtual void ProcessInputRightBumper_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRightBumper_Released();
	void ProcessInputRightBumper_Released_Implementation() { ProcessInputRightBumper_Released_Internal(); }
	virtual void ProcessInputRightBumper_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputStart();
	void ProcessInputStart_Implementation() { ProcessInputStart_Internal(); }
	virtual void ProcessInputStart_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputStart_Released();
	void ProcessInputStart_Released_Implementation() { ProcessInputStart_Released_Internal(); }
	virtual void ProcessInputStart_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputBack();
	void ProcessInputBack_Implementation() { ProcessInputBack_Internal(); }
	virtual void ProcessInputBack_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputBack_Released();
	void ProcessInputBack_Released_Implementation() { ProcessInputBack_Released_Internal(); }
	virtual void ProcessInputBack_Released_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputLeftTrigger(float val);
	void ProcessInputLeftTrigger_Implementation(float val) { ProcessInputLeftTrigger_Internal(val); }
	virtual void ProcessInputLeftTrigger_Internal(float val) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRightTrigger(float val);
	void ProcessInputRightTrigger_Implementation(float val) { ProcessInputRightTrigger_Internal(val); }
	virtual void ProcessInputRightTrigger_Internal(float val) {}


	//Yaw
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRotateRight(float val);
	void ProcessInputRotateRight_Implementation(float val) { ProcessInputRotateRight_Internal(val); }
	virtual void ProcessInputRotateRight_Internal(float val) {}


	//Pitch
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputRotateUp(float val);
	void ProcessInputRotateUp_Implementation(float val) { ProcessInputRotateUp_Internal(val); }
	virtual void ProcessInputRotateUp_Internal(float val) {}

	
	/** @param Rate	This is a normalized rate, 1.0 means full rate */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
	void ProcessInputTurnAtRate(float val);
	void ProcessInputTurnAtRate_Implementation(float val) { ProcessInputTurnAtRate_Internal(val); }
	virtual void ProcessInputTurnAtRate_Internal(float val) {}


	/** @param Rate	This is a normalized rate, 1.0 means full rate */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void ProcessInputLookUpAtRate(float val);
	void ProcessInputLookUpAtRate_Implementation(float val) { ProcessInputLookUpAtRate_Internal(val); }
	virtual void ProcessInputLookUpAtRate_Internal(float val) {};

	
};
