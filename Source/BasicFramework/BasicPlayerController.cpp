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

	PossessBasicPawn(GetPawn());
}


void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Gameplay key bindings
	check(InputComponent);

	InputComponent->bBlockInput = false;

	InputComponent->BindAction(*buttonA, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonA).bConsumeInput = false;
	InputComponent->BindAction(*buttonA, IE_Released, this, &ABasicPlayerController::ProcessInputButtonA_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonB, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonB).bConsumeInput = false;
	InputComponent->BindAction(*buttonB, IE_Released, this, &ABasicPlayerController::ProcessInputButtonB_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonX, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonX).bConsumeInput = false;
	InputComponent->BindAction(*buttonX, IE_Released, this, &ABasicPlayerController::ProcessInputButtonX_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonY, IE_Pressed, this, &ABasicPlayerController::ProcessInputButtonY).bConsumeInput = false;
	InputComponent->BindAction(*buttonY, IE_Released, this, &ABasicPlayerController::ProcessInputButtonY_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonLB, IE_Pressed, this, &ABasicPlayerController::ProcessInputLeftBumper).bConsumeInput = false;
	InputComponent->BindAction(*buttonLB, IE_Released, this, &ABasicPlayerController::ProcessInputLeftBumper_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonRB, IE_Pressed, this, &ABasicPlayerController::ProcessInputRightBumper).bConsumeInput = false;
	InputComponent->BindAction(*buttonRB, IE_Released, this, &ABasicPlayerController::ProcessInputRightBumper_Released).bConsumeInput = false;

	InputComponent->BindAction(*buttonStart, IE_Pressed, this, &ABasicPlayerController::ProcessInputStart).bConsumeInput = false;
	FInputActionBinding pause = InputComponent->BindAction(*buttonStart, IE_Released, this, &ABasicPlayerController::ProcessInputStart_Released);
	pause.bConsumeInput = false;
	pause.bExecuteWhenPaused = true; //Because it's the pause button

	InputComponent->BindAction(*buttonBack, IE_Pressed, this, &ABasicPlayerController::ProcessInputBack).bConsumeInput = false;
	InputComponent->BindAction(*buttonBack, IE_Released, this, &ABasicPlayerController::ProcessInputBack_Released).bConsumeInput = false;

	InputComponent->BindAxis("MoveForward", this, &ABasicPlayerController::ProcessInputForward).bConsumeInput = false;
	InputComponent->BindAxis("MoveRight", this, &ABasicPlayerController::ProcessInputRight).bConsumeInput = false;

	// "turn" deals with absolute deltas, such as mouse devices.
	// "turnrate" deal with rates of change, such as analog joysticks.
	InputComponent->BindAxis("Turn", this, &ABasicPlayerController::ProcessInputRotateRight).bConsumeInput = false;
	InputComponent->BindAxis("TurnRate", this, &ABasicPlayerController::ProcessInputTurnAtRate).bConsumeInput = false;
	InputComponent->BindAxis("LookUp", this, &ABasicPlayerController::ProcessInputRotateUp).bConsumeInput = false;
	InputComponent->BindAxis("LookUpRate", this, &ABasicPlayerController::ProcessInputLookUpAtRate).bConsumeInput = false;

	InputComponent->BindAxis("LeftTrigger", this, &ABasicPlayerController::ProcessInputLeftTrigger).bConsumeInput = false;
	InputComponent->BindAxis("RightTrigger", this, &ABasicPlayerController::ProcessInputRightTrigger).bConsumeInput = false;

}

void ABasicPlayerController::ResetInputDelegates()
{
	delInputButtonA_Pressed.Clear();
	delInputButtonA_Released.Clear();
	delInputButtonB_Pressed.Clear();
	delInputButtonB_Released.Clear();
	delInputButtonX_Pressed.Clear();
	delInputButtonX_Released.Clear();
	delInputButtonY_Pressed.Clear();
	delInputButtonY_Released.Clear();
	delInputLeftBumper_Pressed.Clear();
	delInputLeftBumper_Released.Clear();
	delInputRightBumper_Pressed.Clear();
	delInputRightBumper_Released.Clear();
	delInputStart_Pressed.Clear();
	delInputStart_Released.Clear();
	delInputBack_Pressed.Clear();
	delInputBack_Released.Clear();
	delInputLeftTrigger.Clear();
	delInputRightTrigger.Clear();
	delInputForward.Clear();
	delInputRight.Clear();
	delInputTurnAtRate.Clear();
	delInputLookUpAtRate.Clear();
	delInputRotateRight.Clear();
	delInputRotateUp.Clear();
}


void ABasicPlayerController::PossessBasicPawn(APawn* pCharacter)
{ 
	IBasicPawnInterface* interf = Cast<IBasicPawnInterface>(pCharacter);
	check(interf != nullptr);

	if (interf == nullptr) return;
	
	if (characterPawnInterface != nullptr) IBasicPawnInterface::Execute_OnUnpossess(interf->_getUObject());
	Possess(pCharacter);

	characterPawnInterface = interf;
	IBasicPawnInterface::Execute_OnPossess(interf->_getUObject(), GetInputIndex());
	ResetInputDelegates();
	IBasicPawnInterface::Execute_SetUpPlayerControllerInput(interf->_getUObject(), this);
}


/** ----------------------------- INPUT PROCESSING -------------------------------*/

void ABasicPlayerController::ProcessInputButtonA()
{
	if (delInputButtonA_Pressed.IsBound()) delInputButtonA_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonA_Released()
{
	if (delInputButtonA_Released.IsBound()) delInputButtonA_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonB()
{
	if (delInputButtonB_Pressed.IsBound()) delInputButtonB_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonB_Released()
{
	if (delInputButtonB_Released.IsBound()) delInputButtonB_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonX()
{
	if (delInputButtonX_Pressed.IsBound()) delInputButtonX_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonX_Released()
{
	if (delInputButtonX_Released.IsBound()) delInputButtonX_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonY()
{
	if (delInputButtonY_Pressed.IsBound()) delInputButtonY_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputButtonY_Released()
{
	if (delInputButtonY_Released.IsBound()) delInputButtonY_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputLeftBumper()
{
	if (delInputLeftBumper_Pressed.IsBound()) delInputLeftBumper_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputLeftBumper_Released()
{
	if (delInputLeftBumper_Released.IsBound()) delInputLeftBumper_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputRightBumper()
{
	if (delInputRightBumper_Pressed.IsBound()) delInputRightBumper_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputRightBumper_Released()
{
	if (delInputRightBumper_Released.IsBound()) delInputRightBumper_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputStart()
{
	if (delInputStart_Pressed.IsBound()) delInputStart_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputStart_Released()
{
	if (delInputStart_Released.IsBound()) delInputStart_Released.Broadcast();
}


void ABasicPlayerController::ProcessInputBack()
{
	if (delInputBack_Pressed.IsBound()) delInputBack_Pressed.Broadcast();
}


void ABasicPlayerController::ProcessInputBack_Released()
{
	if (delInputBack_Released.IsBound()) delInputBack_Released.Broadcast();
}

void ABasicPlayerController::ProcessInputLeftTrigger(float val)
{
	if (delInputLeftTrigger.IsBound()) delInputLeftTrigger.Broadcast(val);
}

void ABasicPlayerController::ProcessInputRightTrigger(float val)
{
	if (delInputRightTrigger.IsBound()) delInputRightTrigger.Broadcast(val);
}


void ABasicPlayerController::ProcessInputForward(float val)
{
	if (delInputForward.IsBound()) delInputForward.Broadcast(val);
}


void ABasicPlayerController::ProcessInputRight(float val)
{
	if (delInputRight.IsBound()) delInputRight.Broadcast(val);
}


void ABasicPlayerController::ProcessInputTurnAtRate(float rate)
{
	if (delInputTurnAtRate.IsBound()) delInputTurnAtRate.Broadcast(rate);
}


void ABasicPlayerController::ProcessInputLookUpAtRate(float rate)
{
	if (delInputLookUpAtRate.IsBound()) delInputLookUpAtRate.Broadcast(rate);
}


void ABasicPlayerController::ProcessInputRotateRight(float val)
{
	if (delInputRotateRight.IsBound()) delInputRotateRight.Broadcast(val);
}


void ABasicPlayerController::ProcessInputRotateUp(float val)
{
	if (delInputRotateUp.IsBound()) delInputRotateUp.Broadcast(val);
}
