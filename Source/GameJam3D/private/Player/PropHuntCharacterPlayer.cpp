// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJam3D/Public/Player/PropHuntCharacterPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameJam3D/public/PlayerController/PropHuntPlayerController.h"


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
	
}

// Called every frame
void APropHuntCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	
}

void APropHuntCharacterPlayer::SetPlayerController()
{
	PropHuntPlayerController = Cast<APropHuntPlayerController>(Controller);
}

void APropHuntCharacterPlayer::MoveAction(FVector2D MoveDir)
{
	AddMovementInput(GetActorForwardVector() * MoveDir.Y + GetActorRightVector() * MoveDir.X);
}

void APropHuntCharacterPlayer::LookAction(FVector2D LookDir)
{
	if (PropHuntPlayerController == nullptr) return;

	float PitchValue = LookDir.Y * GetWorld()->DeltaTimeSeconds * 100.f;

	float YawValue = LookDir.X * GetWorld()->DeltaTimeSeconds * 100.f;
	
	AddActorLocalRotation(FRotator(0.f, YawValue, 0.f), true);

	if (CameraComponent == nullptr) return;

	CameraComponent->AddLocalRotation(FRotator(PitchValue, 0.f, 0.f), true);
	
	FMath::Clamp(CameraComponent->GetRelativeRotation().Yaw, -70.f, 70.f);
}

void APropHuntCharacterPlayer::CatchAction(float CatchValue)
{
	CatchActionBlueprint(CatchValue);
}

void APropHuntCharacterPlayer::JumpAction(float JumpValue)
{
	GEngine->AddOnScreenDebugMessage(
			-1,
			3.f,
			FColor::Red,
			TEXT("TriggerJump")
		);
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("JumpAction")
	);
		Jump();
	}
}

