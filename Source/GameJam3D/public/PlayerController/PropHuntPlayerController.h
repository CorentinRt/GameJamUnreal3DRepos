// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "PropHuntPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAMEJAM3D_API APropHuntPlayerController : public APlayerController
{
	GENERATED_BODY()
	
#pragma region Mapping Context / Input Data
	
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> MoveInputAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> LookInputAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> CatchInputAction;

protected:
	virtual void BeginPlay() override;
	
	void SetupMappingContextIntoController() const;

	virtual void SetupInputComponent() override;
#pragma endregion

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMoveAction, FVector2D, InputMoveValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputLookAction, FVector2D, InputLookValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputCatchAction, float, InputCatchValue);

	FOnInputMoveAction OnInputMoveAction;
	FOnInputLookAction OnInputLookAction;
	FOnInputCatchAction OnInputCatchAction;

	
private:
	void MoveAction(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindMoveInput(UEnhancedInputComponent* EnhancedInputComponent);

	void LookAction(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindLookInput(UEnhancedInputComponent* EnhancedInputComponent);


	void CatchAction(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindCatchInput(UEnhancedInputComponent* EnhancedInputComponent);
	
};
