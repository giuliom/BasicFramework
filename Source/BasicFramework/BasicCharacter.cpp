#include "BasicCharacter.h"

#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "BasicPlayerController.h"
#include "Camera/CameraComponent.h"
#include "BasicInteractionType.h"
#include "BasicUtils.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values
ABasicCharacter::ABasicCharacter(const FObjectInitializer & ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->RelativeLocation = FVector(0.0f, 20.0f, 00.0f); // Position the camera
	firstPersonCameraComponent->RelativeRotation = FRotator(0.0f, 90.0f, 0.0f);
	USceneComponent* mesh = (USceneComponent*) GetMesh();
	firstPersonCameraComponent->SetupAttachment(mesh , cameraSocket);
	firstPersonCameraComponent->bUsePawnControlRotation = true;

	movementComponent = GetCharacterMovement();
}


// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	maxSpeedCached = movementComponent->MaxWalkSpeed;
}


// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABasicCharacter::SetRunning(bool val)
{
	if (!bCanRun && val) return;
	bIsRunning = val;

	movementComponent->MaxWalkSpeed = val ? maxSpeedCached * runningSpeedMultiplier : maxSpeedCached;
}

void ABasicCharacter::SetSwimming(bool enabled)
{
	if (enabled) 
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}

	bUseControllerRotationPitch = enabled;
}


//----------------------- GAMEPLAY METHODS -----------------------

bool ABasicCharacter::Interact(EBasicInteractionType iType)
{
	
	FHitResult hit;
	UBasicInteractionComponent* result = Cast<UBasicInteractionComponent>(UBasicUtils::LineTraceComponent
				(hit, this, UBasicInteractionComponent::StaticClass(), firstPersonCameraComponent->GetComponentLocation(), firstPersonCameraComponent->GetComponentLocation() + (firstPersonCameraComponent->GetForwardVector() * defaultRaycastDistance),
				ECollisionChannel::ECC_GameTraceChannel1,true));

	if (result != nullptr)
	{

		if (result->CanBeExecuted() )
		{
			UActorComponent* component = (UActorComponent*)hit.GetComponent();
			result->Execute(this, component, iType);
			return true;
		}
	}
	return false;
}

void ABasicCharacter::OnPossess_Internal(int32 index)
{
	playerIndex = index;
}

void ABasicCharacter::OnUnpossess_Internal()
{
	playerIndex = -1;
}


//----------------------- MOVEMENT METHODS -----------------------

void ABasicCharacter::Jump()
{
	if (!bMovementEnabled || !bCanJump) return;

	bIsJumping = true;
	Super::Jump();
}


void ABasicCharacter::StopJumping()
{
	if (!bMovementEnabled) return;

	bIsJumping = false;
	Super::StopJumping();
}


//----------------------- INPUT PROCESSING METHODS -----------------------

void ABasicCharacter::ProcessInputForward_Internal(float val)
{
	if (val != 0.0f && bMovementEnabled)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), val);
	}
}


void ABasicCharacter::ProcessInputRight_Internal(float val)
{
	if (val != 0.0f && bMovementEnabled)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), val);
	}
}


void ABasicCharacter::ProcessInputButtonA_Internal()
{

}

void ABasicCharacter::ProcessInputButtonA_Released_Internal()
{
	Interact();
}


void ABasicCharacter::ProcessInputButtonB_Internal()
{

}


void ABasicCharacter::ProcessInputButtonB_Released_Internal()
{

}


void ABasicCharacter::ProcessInputButtonX_Internal()
{
	Jump();
}


void ABasicCharacter::ProcessInputButtonX_Released_Internal()
{
	StopJumping();
}


void ABasicCharacter::ProcessInputButtonY_Internal()
{

}


void ABasicCharacter::ProcessInputButtonY_Released_Internal()
{

}


void ABasicCharacter::ProcessInputLeftBumper_Internal()
{
	SetRunning(true);
}


void ABasicCharacter::ProcessInputLeftBumper_Released_Internal()
{
	SetRunning(false);
}


void ABasicCharacter::ProcessInputRightBumper_Internal()
{
	
}


void ABasicCharacter::ProcessInputRightBumper_Released_Internal()
{
	
}

void ABasicCharacter::ProcessInputStart_Internal()
{
}

void ABasicCharacter::ProcessInputStart_Released_Internal()
{
}

void ABasicCharacter::ProcessInputBack_Internal()
{
}

void ABasicCharacter::ProcessInputBack_Released_Internal()
{
}

void ABasicCharacter::ProcessInputLeftTrigger_Internal(float val)
{
}

void ABasicCharacter::ProcessInputRightTrigger_Internal(float val)
{
}


void ABasicCharacter::ProcessInputRotateRight_Internal(float val) //Yaw
{
	if (!bRotationEnabled) return;

	Super::AddControllerYawInput(val);
}


void ABasicCharacter::ProcessInputRotateUp_Internal(float val) //Pitch
{
	if (!bRotationEnabled) return;

	Super::AddControllerPitchInput(val);
}


void ABasicCharacter::ProcessInputTurnAtRate_Internal(float val)
{
	if (!bRotationEnabled) return;

	// calculate delta for this frame from the rate information
	ProcessInputRotateRight_Internal(val * BaseTurnRate * turnRateMultiplier * GetWorld()->GetDeltaSeconds());
}


void ABasicCharacter::ProcessInputLookUpAtRate_Internal(float val)
{
	if (!bRotationEnabled) return;

	// calculate delta for this frame from the rate information
	ProcessInputRotateUp_Internal(val * BaseLookUpRate * lookUpRateMultiplier * GetWorld()->GetDeltaSeconds());
}
