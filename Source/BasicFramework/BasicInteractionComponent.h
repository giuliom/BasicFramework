// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInteractionEvent, UObject*, caller, UActorComponent*, component, EBasicInteractionType, interactionType);

UCLASS(BlueprintType, Blueprintable, ClassGroup=(Gameplay), meta = (BlueprintSpawnableComponent))
class BASICFRAMEWORK_API UBasicInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/** If the actor can be interacted upon */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bExecutionAllowed = true;

	/** If there can be multiple interactions at the same time */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSingleInteraction = true;

	/** If Async one or more of the Execution() methods are asynchronous therefore every one must call the following method when it's execution is completed */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsAsync = false;

	UPROPERTY(BlueprintReadWrite)
	bool bInteractionInProgress = false;

	//Delegate fired when Execute() is completed by PostExecutionSetup()
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnInteractionCompleted;
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void PreExecutionSetup();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void PostExecutionSetup(EBasicInteractionType interactionType);

public:
	// Sets default values for this component's properties
	UBasicInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnPreExecution;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnExecution;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FInteractionEvent OnPostExecution;
	

	/**
	* Blueprintcallable function that represent the interaction event
	*
	* @param caller the UObject firing the interaction
	* @param component of the object implementing this interface that has received the interaction
	* @param interactionType represent different types of interaction possible with the object
	*/
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void Execute(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CanBeExecuted() { return bExecutionAllowed; }

	UFUNCTION(BlueprintCallable)
		void SetCanBeExecuted(bool val) { bExecutionAllowed = val; }

};
