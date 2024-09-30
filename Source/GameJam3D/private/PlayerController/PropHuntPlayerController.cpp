// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJam3D/Public/PlayerController/PropHuntPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameJam3D/Public/Player/PropHuntCharacterPlayer.h"

void APropHuntPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APropHuntPlayerController::SetupMappingContextIntoController() const
{
	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (LocalPlayer == nullptr) return;

	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (InputSystem == nullptr) return;

	if (InputMappingContext == nullptr) return;
	
	InputSystem->AddMappingContext(InputMappingContext, 0);
}

void APropHuntPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetupMappingContextIntoController();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent == nullptr) return;

	BindMoveInput(EnhancedInputComponent);
	BindLookInput(EnhancedInputComponent);
	BindCatchInput(EnhancedInputComponent);
	BindJumpAction(EnhancedInputComponent);
}

void APropHuntPlayerController::MoveReceiveInput(const FInputActionValue& InputActionValue)
{
	FVector2D MoveValue = InputActionValue.Get<FVector2D>();
	
	OnInputMoveAction.Broadcast(MoveValue);
}

void APropHuntPlayerController::BindMoveInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent == nullptr) return;

	if (MoveInputAction == nullptr) return;
	
	EnhancedInputComponent->BindAction(
		MoveInputAction,
		ETriggerEvent::Started,
		this,
		&APropHuntPlayerController::MoveReceiveInput
	);
	EnhancedInputComponent->BindAction(
		MoveInputAction,
		ETriggerEvent::Triggered,
		this,
		&APropHuntPlayerController::MoveReceiveInput
	);
	EnhancedInputComponent->BindAction(
		MoveInputAction,
		ETriggerEvent::Completed,
		this,
		&APropHuntPlayerController::MoveReceiveInput
	);
}

void APropHuntPlayerController::LookReceiveInput(const FInputActionValue& InputActionValue)
{
	FVector2D LookValue = InputActionValue.Get<FVector2D>();

	OnInputLookAction.Broadcast(LookValue);
}

void APropHuntPlayerController::BindLookInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent == nullptr) return;

	if (LookInputAction == nullptr) return;
	
	EnhancedInputComponent->BindAction(
		LookInputAction,
		ETriggerEvent::Started,
		this,
		&APropHuntPlayerController::LookReceiveInput
	);
	EnhancedInputComponent->BindAction(
		LookInputAction,
		ETriggerEvent::Triggered,
		this,
		&APropHuntPlayerController::LookReceiveInput
	);
	EnhancedInputComponent->BindAction(
		LookInputAction,
		ETriggerEvent::Completed,
		this,
	&APropHuntPlayerController::LookReceiveInput
	);
}

void APropHuntPlayerController::CatchReceiveInput(const FInputActionValue& InputActionValue)
{
	float CatchValue = InputActionValue.Get<float>();

	OnInputCatchAction.Broadcast(CatchValue);
}

void APropHuntPlayerController::BindCatchInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent == nullptr) return;

	if (CatchInputAction == nullptr) return;
	
	EnhancedInputComponent->BindAction(
		CatchInputAction,
		ETriggerEvent::Started,
		this,
		&APropHuntPlayerController::CatchReceiveInput
	);
}

void APropHuntPlayerController::JumpReceiveInput(const FInputActionValue& InputActionValue)
{
	float JumpValue = InputActionValue.Get<float>();

	OnInputJumpAction.Broadcast(JumpValue);
}

void APropHuntPlayerController::BindJumpAction(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (EnhancedInputComponent == nullptr) return;

	if (JumpInputAction == nullptr) return;
	
	EnhancedInputComponent->BindAction(
		JumpInputAction,
		ETriggerEvent::Started,
		this,
		&APropHuntPlayerController::JumpReceiveInput
	);
}
