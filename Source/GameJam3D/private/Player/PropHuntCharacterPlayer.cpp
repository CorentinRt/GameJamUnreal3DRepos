// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJam3D/Public/Player/PropHuntCharacterPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameJam3D/public/PlayerController/PropHuntPlayerController.h"
#include "Player/PropHuntCharacterDataAsset.h"


// Sets default values
APropHuntCharacterPlayer::APropHuntCharacterPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraPlayer"));

	CameraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APropHuntCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerController();

	BindReceiveInputFromController();

	SetupParameters();
}

// Called every frame
void APropHuntCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleRandomMovement(DeltaTime);
	HandleCatchCoolDown(DeltaTime);
}

// Called to bind functionality to input
void APropHuntCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APropHuntCharacterPlayer::BindReceiveInputFromController() const
{
	if (PropHuntPlayerController == nullptr) return;
	
	PropHuntPlayerController->OnInputMoveAction.AddDynamic(this, &APropHuntCharacterPlayer::MoveAction);
	PropHuntPlayerController->OnInputLookAction.AddDynamic(this, &APropHuntCharacterPlayer::LookAction);
	PropHuntPlayerController->OnInputCatchAction.AddDynamic(this, &APropHuntCharacterPlayer::CatchAction);
	PropHuntPlayerController->OnInputJumpAction.AddDynamic(this, &APropHuntCharacterPlayer::JumpAction);
	PropHuntPlayerController->OnInputQTEAction.AddDynamic(this, &APropHuntCharacterPlayer::QTEAction);
	
}

void APropHuntCharacterPlayer::SetPlayerController()
{
	PropHuntPlayerController = Cast<APropHuntPlayerController>(Controller);
}

void APropHuntCharacterPlayer::SetupParameters()
{
	if (PropHuntCharacterDataAsset == nullptr) return;


	// Catch parameters Setup
	CatchCooldown = PropHuntCharacterDataAsset->CatchCooldown;


	// RandomMoveParameters Setup
	MaxRandomMoveStrenght = PropHuntCharacterDataAsset->MaxRandomMoveStrenght;
	TimeBeforeRandomDirChange = PropHuntCharacterDataAsset->TimeBeforeRandomDirChange;
	MaxCameraAngleEffect = PropHuntCharacterDataAsset->MaxCameraAngleEffect;
	CameraAngleEffectSpeed = PropHuntCharacterDataAsset->CameraAngleEffectSpeed;
	
}

void APropHuntCharacterPlayer::MoveAction(FVector2D MoveDir)
{
	AddMovementInput(GetActorForwardVector() * MoveDir.Y + GetActorRightVector() * MoveDir.X);
}

void APropHuntCharacterPlayer::LookAction(FVector2D LookDir)
{
	if (PropHuntPlayerController == nullptr) return;

	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	
	float PitchValue = LookDir.Y * DeltaTime * 100.f;

	float YawValue = LookDir.X * DeltaTime * 100.f;
	
	AddActorLocalRotation(FRotator(0.f, YawValue, 0.f), true);

	if (CameraComponent == nullptr) return;

	CameraComponent->AddLocalRotation(FRotator(PitchValue, 0.f, 0.f), true);
	
	FMath::Clamp(CameraComponent->GetRelativeRotation().Yaw, -70.f, 70.f);
}

void APropHuntCharacterPlayer::CatchAction(float CatchValue)
{
	if (CanCatch)
	{
		CanCatch = false;
		CatchActionBlueprint(CatchValue);
	}
}

void APropHuntCharacterPlayer::HandleCatchCoolDown(float DeltaTime)
{
	if (CanCatch) return;
	
	if (CurrentCatchCooldown <= 0.f)
	{
		CanCatch = true;
		CurrentCatchCooldown = CatchCooldown;
	}
	else
	{
		CurrentCatchCooldown -= DeltaTime;
	}
}

void APropHuntCharacterPlayer::JumpAction(float JumpValue)
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		Jump();
	}
}

void APropHuntCharacterPlayer::HandleRandomMovement(float DeltaTime)
{
	HandleCameraRandomEffect(DeltaTime);
	
	if (IsMovingRandomly == false) return;
	
	if (CurrentTimeBeforeChange <= 0.f)
	{
		ChangeRandomDirection();

		CurrentTimeBeforeChange = TimeBeforeRandomDirChange;
	}
	else
	{
		CurrentTimeBeforeChange -= DeltaTime;
	}
	
	CurrentRandomMovementDir.X = FMath::FInterpTo(CurrentRandomMovementDir.X, TargetRandomMovementDir.X, DeltaTime, 1.f);
	CurrentRandomMovementDir.Y = FMath::FInterpTo(CurrentRandomMovementDir.Y, TargetRandomMovementDir.Y, DeltaTime, 1.f);

	GEngine->AddOnScreenDebugMessage(
				-1,
				3.f,
				FColor::Purple,
				FString::Printf(TEXT("Player Movement: %f"), CurrentRandomMovementDir.X)
			);
	
	GetCharacterMovement()->AddInputVector(FVector(CurrentRandomMovementDir.X, CurrentRandomMovementDir.Y, 0.f) * MaxRandomMoveStrenght);
}

void APropHuntCharacterPlayer::ChangeRandomDirection()
{
	GEngine->AddOnScreenDebugMessage(
				-1,
				3.f,
				FColor::Red,
				TEXT("ChangeRandomDirection")
			);
	
	float XRandomTarget = FMath::FRandRange(-1.f , 1.f);
	float YRandomTarget = FMath::FRandRange(-1.f , 1.f);

	TargetRandomMovementDir.X = XRandomTarget;
	TargetRandomMovementDir.Y = YRandomTarget;

	TargetRandomMovementDir.Normalize();
}

void APropHuntCharacterPlayer::SetCharacterRandomMovement(bool IsRandom)
{
	IsMovingRandomly = IsRandom;
	
	if (IsMovingRandomly == false)
	{
		CurrentRandomMovementDir = FVector2D(0.f, 0.f);

		CurrentTimeBeforeChange = 0.f;
	}
}

void APropHuntCharacterPlayer::HandleCameraRandomEffect(float DeltaTime)
{
	if (CameraComponent == nullptr) return;
	
	FRotator CurrentCameraRotation = CameraComponent->GetRelativeRotation();
	if (!IsMovingRandomly)
	{
		CurrentCameraRotation.Roll = FMath::FInterpTo(CurrentCameraRotation.Roll, 0.f, DeltaTime, 1.f);
	}
	else
	{
		float TargetRoll = CurrentCameraRotation.Roll + FMath::Sign(CurrentRandomMovementDir.X) * DeltaTime * 100.f;

		TargetRoll = FMath::Clamp(TargetRoll, -MaxCameraAngleEffect, MaxCameraAngleEffect);
		
		CurrentCameraRotation.Roll = FMath::FInterpTo(CurrentCameraRotation.Roll, TargetRoll, DeltaTime, CameraAngleEffectSpeed);
	}
	CameraComponent->SetRelativeRotation(CurrentCameraRotation);
}

void APropHuntCharacterPlayer::QTEAction(float QTEValue)
{
	QTEActionBlueprint(QTEValue);
}
