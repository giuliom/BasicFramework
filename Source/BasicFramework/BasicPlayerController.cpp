#include "BasicPlayerController.h"
#include "Camera/CameraComponent.h"
#include "BasicPawnInterface.h"

ABasicPlayerController::ABasicPlayerController()
{
	
}


void ABasicPlayerController::BeginPlay()
{
	characterPawnInterface = Cast<IBasicPawnInterface>(GetPawn());
	cameraManager = (ABasicPlayerCameraManager*)PlayerCameraManager;
}


void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Gameplay key bindings
	check(InputComponent);

	InputComponent->bBlockInput = false;

	InputComponent->BindAction(*buttonA, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonA);
	InputComponent->BindAction(*buttonA, IE_Released, this, &ABasicPlayerController::ProcessInputButtonA_Released);

	InputComponent->BindAction(*buttonB, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonB);
	InputComponent->BindAction(*buttonB, IE_Released, this, &ABasicPlayerController::ProcessInputButtonB_Released);

	InputComponent->BindAction(*buttonX, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonX);
	InputComponent->BindAction(*buttonX, IE_Released, this, &ABasicPlayerController::ProcessInputButtonX_Released);

	InputComponent->BindAction(*buttonY, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonY);
	InputComponent->BindAction(*buttonY, IE_Released, this, &ABasicPlayerController::ProcessInputButtonY_Released);

	InputComponent->BindAction(*buttonLB, IE_Pressed, this, &ABasicPlayerController::ProcessInputLeftBumper);
	InputComponent->BindAction(*buttonLB, IE_Released, this, &ABasicPlayerController::ProcessInputLeftBumper_Released);

	InputComponent->BindAction(*buttonRB, IE_Pressed, this, &ABasicPlayerController::ProcessInputRightBumper);
	InputComponent->BindAction(*buttonRB, IE_Released, this, &ABasicPlayerController::ProcessInputRightBumper_Released);

	InputComponent->BindAction(*buttonStart, IE_Pressed, this, &ABasicPlayerController::ProcessInputStart);
	InputComponent->BindAction(*buttonStart, IE_Released, this, &ABasicPlayerController::ProcessInputStart_Released);

	InputComponent->BindAction(*buttonBack, IE_Pressed, this, &ABasicPlayerController::ProcessInputBack);
	InputComponent->BindAction(*buttonBack, IE_Released, this, &ABasicPlayerController::ProcessInputBack_Released);

	InputComponent->BindAxis("MoveForward", this, &ABasicPlayerController::ProcessInputForward);
	InputComponent->BindAxis("MoveRight", this, &ABasicPlayerController::ProcessInputRight);

	// "turn" deals with absolute deltas, such as mouse devices.
	// "turnrate" deal with rates of change, such as analog joysticks.
	InputComponent->BindAxis("Turn", this, &ABasicPlayerController::ProcessInputRotateRight);
	InputComponent->BindAxis("TurnRate", this, &ABasicPlayerController::ProcessInputTurnAtRate);
	InputComponent->BindAxis("LookUp", this, &ABasicPlayerController::ProcessInputRotateUp);
	InputComponent->BindAxis("LookUpRate", this, &ABasicPlayerController::ProcessInputLookUpAtRate);

	InputComponent->BindAxis("LeftTrigger", this, &ABasicPlayerController::ProcessInputLeftTrigger);
	InputComponent->BindAxis("RightTrigger", this, &ABasicPlayerController::ProcessInputRightTrigger);

}


void ABasicPlayerController::PossessBasicPawn(APawn* pCharacter)
{ 
	IBasicPawnInterface* interf = Cast<IBasicPawnInterface>(pCharacter);
	check(interf != nullptr);

	if (interf == nullptr) return;
	
	if (characterPawnInterface != nullptr) IBasicPawnInterface::Execute_OnDispossess(interf->_getUObject());
	Possess(pCharacter);

	characterPawnInterface = interf;
	IBasicPawnInterface::Execute_OnPossess(interf->_getUObject(), GetInputIndex());
}


/** ----------------------------- INPUT PROCESSING -------------------------------*/

void ABasicPlayerController::ProcessInputButtonA()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonA(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonA_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonA_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonB()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonB(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonB_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonB_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonX()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonX(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonX_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonX_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonY()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonY(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputButtonY_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputButtonY_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputLeftBumper()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputLeftBumper(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputLeftBumper_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputLeftBumper_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputRightBumper()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRightBumper(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputRightBumper_Released()
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRightBumper_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputStart()
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputStart(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputStart_Released()
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputStart_Released(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputBack()
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputBack(characterPawnInterface->_getUObject());
	}
}


void ABasicPlayerController::ProcessInputBack_Released()
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputBack_Released(characterPawnInterface->_getUObject());
	}
}

void ABasicPlayerController::ProcessInputLeftTrigger(float val)
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputLeftTrigger(characterPawnInterface->_getUObject(), val);
	}
}

void ABasicPlayerController::ProcessInputRightTrigger(float val)
{
	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRightTrigger(characterPawnInterface->_getUObject(), val);
	}
}


void ABasicPlayerController::ProcessInputForward(float val)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputForward(characterPawnInterface->_getUObject() , val);
	}
}


void ABasicPlayerController::ProcessInputRight(float val)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRight(characterPawnInterface->_getUObject(), val);
	}
}


void ABasicPlayerController::ProcessInputTurnAtRate(float Rate)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputTurnAtRate(characterPawnInterface->_getUObject(), Rate);
	}
}


void ABasicPlayerController::ProcessInputLookUpAtRate(float Rate)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputLookUpAtRate(characterPawnInterface->_getUObject(), Rate);
	}
}


void ABasicPlayerController::ProcessInputRotateRight(float val)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRotateRight(characterPawnInterface->_getUObject(), val);
	}
}


void ABasicPlayerController::ProcessInputRotateUp(float val)
{

	if (characterPawnInterface != nullptr)
	{
		IBasicPawnInterface::Execute_ProcessInputRotateUp(characterPawnInterface->_getUObject(), val);
	}
}
