// Fill out your copyright notice in the Description page of Project Settings.


#include "GameJam3D/Public/Player/PropHuntCharacterPlayer.h"


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

