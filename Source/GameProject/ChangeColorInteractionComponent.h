// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicFramework/BasicInteractionComponent.h"
#include "Engine/Classes/Engine/DataTable.h"
#include "ChangeColorInteractionComponent.generated.h"

/**
 * 
 */

 /** Structure that defines a level up table entry */
USTRUCT(BlueprintType)
struct FColorTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FColorTableRow()
		: red(0)
		, green(0)
		, blue(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"))
		uint8 red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"))
		uint8 green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"))
		uint8 blue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "255"))
		uint8 alpha;

	FColor ToFColor() { return FColor(red, green, blue, alpha); }
};


UCLASS(BlueprintType, Blueprintable, ClassGroup = (Gameplay), meta = (BlueprintSpawnableComponent))
class GAMEPROJECT_API UChangeColorInteractionComponent : public UBasicInteractionComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDataTableRowHandle colorTableRow;


protected:
	virtual void ExecuteInternal(UObject* caller, UActorComponent* component = nullptr, UBasicInteractionType* interactionType = nullptr) override;
	
};
