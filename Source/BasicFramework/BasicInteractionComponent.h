// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AsyncWork.h"
#include "BasicInteractionType.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "BasicInteractionComponent.generated.h"

/**
* @author @Giulio_M
* @version 1.0
*
* Component used to handle interaction with objects
* Execute(...) is the method that 3 delegates that can be assigned by C++ or blueprints
*
* PreExecution(...) sets up the interaction
* Execution(...) is the method that must implements the interaction
* PostExecution(...) used to cler the state post interaction
*
*/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInteractionEvent, UObject*, caller, UActorComponent*, component, UBasicInteractionType*, interactionType);



UCLASS(BlueprintType, Blueprintable, ClassGroup=(Gameplay), meta = (BlueprintSpawnableComponent))
class BASICFRAMEWORK_API UBasicInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/** If the actor can be interacted upon */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bExecutionEnabled = true;

	bool bFocused = false;

public:
	// Sets default values for this component's properties
	UBasicInteractionComponent();

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnPreExecution;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnExecution;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnPostExecution;

	//Delegate fired when Execute() is completed by PostExecutionSetup()
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnInteractionCompleted;
	

	/**
	* BlueprintNativeEvent function that represent the interaction event
	*
	* @param caller the UObject firing the interaction
	* @param component of the object implementing this interface that has received the interaction
	* @param interactionType represent different types of interaction possible with the object
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void Execute(UObject* caller, UActorComponent* component = nullptr, UBasicInteractionType* interactionType = nullptr);
	virtual void Execute_Implementation(UObject* caller, UActorComponent* component = nullptr, UBasicInteractionType* interactionType = nullptr);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void OnFocusBegin(AActor * byActor = nullptr);
	virtual void OnFocusBegin_Implementation(AActor * byActor = nullptr);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void OnFocusEnd(AActor * byActor = nullptr);
	virtual void OnFocusEnd_Implementation(AActor * byActor = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsFocused() { return bFocused; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual bool IsExecutionEnabled() { return bExecutionEnabled; }

	UFUNCTION(BlueprintCallable)
	virtual void SetCanBeExecuted(bool val) { bExecutionEnabled = val; }

};
