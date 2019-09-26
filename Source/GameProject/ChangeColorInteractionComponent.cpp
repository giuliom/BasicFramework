// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeColorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/Classes/Materials/MaterialInstanceDynamic.h"

void UChangeColorInteractionComponent::ExecuteInternal(UObject* caller, UActorComponent* component, UBasicInteractionType* interactionType)
{
	AActor* actor = GetOwner();

	UActorComponent* actorComponent = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());

	if (actorComponent != nullptr)
	{
		UStaticMeshComponent* staticMeshComponent = static_cast<UStaticMeshComponent*>(actorComponent);

		if (staticMeshComponent != nullptr)
		{
			UMaterialInterface* material = staticMeshComponent->GetMaterial(0);
			UMaterialInstanceDynamic* matInstance = staticMeshComponent->CreateDynamicMaterialInstance(0, material);

			if (matInstance != nullptr)
			{
				auto row = colorTableRow.GetRow<FColorTableRow>("ChangeColorInteractionComponent");

				if (row != nullptr)
				{
					//The material of the mesh must have the parameter color
					matInstance->SetVectorParameterValue("color", row->ToFColor());
				}
			}
		}
	}
}
