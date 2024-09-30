// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJam3D/Public/Player/PropHuntCharacterPlayer.h"

#include "GameJam3D/public/PlayerController/PropHuntPlayerController.h"


// Sets default values
APropHuntCharacterPlayer::APropHuntCharacterPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	
}

void APropHuntCharacterPlayer::SetPlayerController()
{
	PropHuntPlayerController = Cast<APropHuntPlayerController>(Controller);
}

void APropHuntCharacterPlayer::MoveAction(FVector2D MoveDir)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Move")
	);
	
	AddMovementInput(GetActorForwardVector() * MoveDir.Y + GetActorRightVector() * MoveDir.X);
}

void APropHuntCharacterPlayer::LookAction(FVector2D LookDir)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		3.f,
		FColor::Red,
		TEXT("Look")
	);
}

