// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicInteractionType.h"
#include "InteractionComponent.generated.h"

/**
* @author @Giulio_M
* @version 1.0
*
* Component used to handle interaction with objects
* Execute(...) is the method that calls 3 Blueprint Native Events that can be overridden in C++ or Blueprints
*
* PreExecution(...) sets up the interaction
* Execution(...) is the method that must implements the interaction
* PostExecution(...) used to cle
*
*/

UCLASS(Blueprintable, ClassGroup=(Interaction), meta=(InteractiveComponent) )
class BASICFRAMEWORK_API UInteractionComponent : public UActorComponent
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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExecutionCompleted, EBasicInteractionType, interactionType);

	//Delegate fired when Execute() is completed by PostExecutionSetup()
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegates)
	FExecutionCompleted OnExecutionCompleted;

private:	
	
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void PreExecutionSetup();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void PreExecution(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void PreExecution_Implementation(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void PreExecution_Internal(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void Execution(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void Execution_Implementation(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void Execution_Internal(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT) {}

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void PostExecution(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void PostExecution_Implementation(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void PostExecution_Internal(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT) {}

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	virtual void PostExecutionSetup(EBasicInteractionType interactionType);

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* BlueprintNativeEvent that represent the interaction event
	*
	* @param caller the UObject firing the interaction
	* @param component of the object implementing this interface that has received the interaction
	* @param interactionType represent different types of interaction possible with the object
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Gameplay)
	void Execute(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	virtual void Execute_Implementation(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT) { Execute_Internal(caller, component, interactionType); }
	virtual void Execute_Internal(UObject* caller, UActorComponent* component = nullptr, EBasicInteractionType interactionType = EBasicInteractionType::DEFAULT);
	
	
	//Returns the delegate OnExecutionCompleted
	FExecutionCompleted& GetOnExecutionCompleted() { return OnExecutionCompleted; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CanBeExecuted() { return bExecutionAllowed; }

	UFUNCTION(BlueprintCallable)
		void SetCanBeExecuted(bool val) { bExecutionAllowed = val; }

};
