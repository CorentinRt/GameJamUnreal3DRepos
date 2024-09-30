﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PropHuntCharacterPlayer.generated.h"

class UCameraComponent;
class APropHuntPlayerController;

UCLASS()
class GAMEJAM3D_API APropHuntCharacterPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APropHuntCharacterPlayer();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UFUNCTION()
	void BindReceiveInputFromController() const;

	UFUNCTION()
	void SetPlayerController();
	
	UPROPERTY()
	APropHuntPlayerController* PropHuntPlayerController;

#pragma region Actions
private:
	UFUNCTION()
	void MoveAction(FVector2D MoveDir);

	UFUNCTION()
	void LookAction(FVector2D LookDir);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CatchActionBlueprint(float CatchValue);

private:
	UFUNCTION()
	void CatchAction(float CatchValue);

	
	UFUNCTION()
	void JumpAction(float JumpValue);

#pragma endregion 
};
