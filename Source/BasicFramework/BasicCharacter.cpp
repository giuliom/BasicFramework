#include "BasicCharacter.h"

#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "BasicPlayerController.h"
#include "Camera/CameraComponent.h"
#include "BasicInteractionType.h"
#include "BasicUtils.h"
#include "BasicGameMode.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"

//#pragma optimize("", off)

// Sets default values
ABasicCharacter::ABasicCharacter(const FObjectInitializer & ObjectInitializer) : ACharacter(ObjectInitializer.SetDefaultSubobjectClass<UBasicCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	firstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->bUsePawnControlRotation = true;

	movementComponent = Cast<UBasicCharacterMovementComponent> (GetCharacterMovement());
}


// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();

	firstPersonCameraComponent->AttachToComponent( GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, cameraSocket);
	firstPersonCameraComponent->RelativeLocation = FVector(0.0f, 20.0f, 00.0f); // Position the camera
	firstPersonCameraComponent->RelativeRotation = FRotator(0.0f, 90.0f, 0.0f);

	maxSpeedCached = movementComponent->MaxWalkSpeed;
}


void ABasicCharacter::PauseGame()
{
	ABasicGameMode* mode = Cast<ABasicGameMode>(GetWorld()->GetAuthGameMode());
	mode->SetGamePaused(!mode->IsGamePaused());
}


// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HighlightInteractableObject();
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

void ABasicCharacter::SetCrouching(bool val)
{
	if (val)
	{
		if (bCanCrouch) {
			Crouch();
		}
	}
	else
	{
		UnCrouch();
	}
}

void ABasicCharacter::SetSwimming(bool enabled)
{
	if (enabled && bCanSwim) 
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

bool ABasicCharacter::Interact(UBasicInteractionType* iType)
{
	FHitResult hit;
	UBasicInteractionComponent* result = Cast<UBasicInteractionComponent>(UBasicUtils::LineTraceComponent
				(hit, this, UBasicInteractionComponent::StaticClass(), firstPersonCameraComponent->GetComponentLocation(), firstPersonCameraComponent->GetComponentLocation() + (firstPersonCameraComponent->GetForwardVector() * defaultRaycastDistance),
				ECollisionChannel::ECC_GameTraceChannel1,true));

	if (result != nullptr)
	{
		if (result->IsExecutionEnabled() )
		{
			UActorComponent* component = (UActorComponent*)hit.GetComponent();
			result->Execute(this, component, iType);
			return true;
		}
	}
	return false;
}

bool ABasicCharacter::HighlightInteractableObject()
{
	FHitResult hit;
	UBasicInteractionComponent* result = Cast<UBasicInteractionComponent>(UBasicUtils::LineTraceComponent
	(hit, this, UBasicInteractionComponent::StaticClass(), firstPersonCameraComponent->GetComponentLocation(), firstPersonCameraComponent->GetComponentLocation() + (firstPersonCameraComponent->GetForwardVector() * defaultRaycastDistance),
		ECollisionChannel::ECC_GameTraceChannel1, true));

	UPrimitiveComponent* primitive = nullptr;
	bool bFound = false;

	if (OnHighlightEvent.IsBound())
	{
		if (prevHighlightedObj != nullptr) OnHighlightEvent.Broadcast(prevHighlightedObj, false);
	}
	else
	{
		if (prevHighlightedObj != nullptr) prevHighlightedObj->SetRenderCustomDepth(false);
	}

	if (result != nullptr)
	{
		primitive = Cast<UPrimitiveComponent> (hit.Actor->GetComponentByClass(UPrimitiveComponent::StaticClass()));
		
		if (result->IsExecutionEnabled() && primitive != nullptr)
		{
			if (OnHighlightEvent.IsBound())
			{
				OnHighlightEvent.Broadcast(primitive, true);
			}
			else
			{
				primitive->SetRenderCustomDepth(true);
			}
			bFound = true;
		}

	}

	prevHighlightedObj = primitive;

	return bFound;
}

void ABasicCharacter::OnPossess_Internal(int32 index)
{
	playerIndex = index;
	
}

void ABasicCharacter::OnUnpossess_Internal()
{
	playerIndex = -1;
}

void ABasicCharacter::SetUpPlayerControllerInput_Implementation(ABasicPlayerController * controller)
{
	check(controller);

	controller->delInputForward.AddDynamic(this, &ABasicCharacter::MoveForward);
	controller->delInputRight.AddDynamic(this, &ABasicCharacter::MoveRight);

	controller->delInputButtonA_Released.AddDynamic(this, &ABasicCharacter::InputInteract);

	controller->delInputButtonB_Released.AddDynamic(this, &ABasicCharacter::CrouchMode);

	controller->delInputButtonX_Pressed.AddDynamic(this, &ABasicCharacter::Jump);
	controller->delInputButtonX_Released.AddDynamic(this, &ABasicCharacter::StopJumping);

	controller->delInputLeftBumper_Pressed.AddDynamic(this, &ABasicCharacter::StartRunning);
	controller->delInputLeftBumper_Released.AddDynamic(this, &ABasicCharacter::StopRunning);

	controller->delInputStart_Released.AddDynamic(this, &ABasicCharacter::PauseGame);

	controller->delInputRotateRight.AddDynamic(this, &ABasicCharacter::RotateRight);
	controller->delInputRotateUp.AddDynamic(this, &ABasicCharacter::RotateUp);

	controller->delInputTurnAtRate.AddDynamic(this, &ABasicCharacter::TurnAtRate);
	controller->delInputLookUpAtRate.AddDynamic(this, &ABasicCharacter::LookUpAtRate);
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


void ABasicCharacter::MoveForward(float val)
{
	if (val != 0.0f && bMovementEnabled)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), val);
	}
}

void ABasicCharacter::MoveRight(float val)
{
	if (val != 0.0f && bMovementEnabled)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), val);
	}
}

void ABasicCharacter::CrouchMode()
{
	bool shouldcrouch = !IsCrouching();
	SetCrouching(shouldcrouch);
}

void ABasicCharacter::InputInteract()
{
	Interact();
}

void ABasicCharacter::StartRunning()
{
	SetRunning(true);
}

void ABasicCharacter::StopRunning()
{
	SetRunning(false);
}


void ABasicCharacter::RotateRight(float val) //Yaw
{
	if (!bRotationEnabled) return;

	Super::AddControllerYawInput(val);
}


void ABasicCharacter::RotateUp(float val) //Pitch
{
	if (!bRotationEnabled) return;

	Super::AddControllerPitchInput(val);
}


void ABasicCharacter::TurnAtRate(float val)
{
	if (!bRotationEnabled) return;

	// calculate delta for this frame from the rate information
	RotateRight(val * BaseTurnRate * turnRateMultiplier * GetWorld()->GetDeltaSeconds());
}


void ABasicCharacter::LookUpAtRate(float val)
{
	if (!bRotationEnabled) return;

	// calculate delta for this frame from the rate information
	RotateUp(val * BaseLookUpRate * lookUpRateMultiplier * GetWorld()->GetDeltaSeconds());
}

//#pragma optimize("", on)