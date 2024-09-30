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
	
}

void APropHuntPlayerController::MoveAction(const FInputActionValue& InputActionValue)
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
		&APropHuntPlayerController::MoveAction
	);
	EnhancedInputComponent->BindAction(
		MoveInputAction,
		ETriggerEvent::Triggered,
		this,
		&APropHuntPlayerController::MoveAction
	);
	EnhancedInputComponent->BindAction(
		MoveInputAction,
		ETriggerEvent::Completed,
		this,
		&APropHuntPlayerController::MoveAction
	);
}

void APropHuntPlayerController::LookAction(const FInputActionValue& InputActionValue)
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
		&APropHuntPlayerController::LookAction
	);
	EnhancedInputComponent->BindAction(
		LookInputAction,
		ETriggerEvent::Triggered,
		this,
		&APropHuntPlayerController::LookAction
	);
	EnhancedInputComponent->BindAction(
		LookInputAction,
		ETriggerEvent::Completed,
		this,
	&APropHuntPlayerController::LookAction
	);
}

void APropHuntPlayerController::CatchAction(const FInputActionValue& InputActionValue)
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
		&APropHuntPlayerController::CatchAction
	);
}
