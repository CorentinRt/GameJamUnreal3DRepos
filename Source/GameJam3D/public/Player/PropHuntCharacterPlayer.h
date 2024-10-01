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

	UPROPERTY(EditAnywhere)
	float CatchForce = 10.f;
	
	UPROPERTY()
	bool CanCatch = true;
	
	UPROPERTY(EditAnywhere)
	float CatchCooldown = 1.5f;

	UPROPERTY()
	float CurrentCatchCooldown = 0.f;

	UFUNCTION()
	void HandleCatchCoolDown(float DeltaTime);
	
	
	UFUNCTION()
	void JumpAction(float JumpValue);

#pragma endregion

#pragma region RandomMovements
private:
	UPROPERTY()
	bool IsMovingRandomly = false;

	UPROPERTY()
	FVector2D TargetRandomMovementDir;
	UPROPERTY()
	FVector2D CurrentRandomMovementDir;

	UPROPERTY(EditAnywhere)
	float MaxRandomStrenght = 3.f;

	UPROPERTY(EditAnywhere)
	float TimeBeforeRandomDirChange = 0.3f;

	UPROPERTY()
	float CurrentTimeBeforeChange = 0.f;
	
	UFUNCTION()
	void HandleRandomMovement(float DeltaTime);

	UFUNCTION()
	void ChangeRandomDirection();
	
public:
	UFUNCTION(BlueprintCallable)
	void SetCharacterRandomMovement(bool IsRandom);
	
#pragma endregion


#pragma region QTE Action

	UFUNCTION()
	void QTEAction(float QTEValue);

	UFUNCTION(BlueprintImplementableEvent)
	void QTEActionBlueprint(float QTEValue);


#pragma endregion 
};
