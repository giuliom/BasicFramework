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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void OnPossess(int32 index);
	void OnPossess_Implementation(int32 index) { OnPossess_Internal(index); }
	virtual void OnPossess_Internal(int32 index) { playerIndex = index; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void OnUnpossess();
	void OnUnpossess_Implementation() { OnUnpossess_Internal(); }
	virtual void OnUnpossess_Internal() {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void SetUpPlayerControllerInput(class ABasicPlayerController* controller);
	virtual void SetUpPlayerControllerInput_Implementation(class ABasicPlayerController* controller) {}

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

	//UFUNCTION(BlueprintCallable)
	FGameplayTag GetGameplayTag() const { return gameplayTag; }

	//UFUNCTION(BlueprintCallable)
	void SetGameplayTag(FGameplayTag t) { gameplayTag = t; }


};
