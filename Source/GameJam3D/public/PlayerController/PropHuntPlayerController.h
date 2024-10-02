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

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> JumpInputAction;


	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> QTEInputMappingContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> QTEInputAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> PauseInputAction;

protected:
	virtual void BeginPlay() override;
	
	void SetupMappingContextIntoController() const;

	virtual void SetupInputComponent() override;
#pragma endregion

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMoveAction, FVector2D, InputMoveValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputLookAction, FVector2D, InputLookValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputCatchAction, float, InputCatchValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputJumpAction, float, InputJumpValue);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputPauseAction, float, InputPauseValue);

	

	FOnInputMoveAction OnInputMoveAction;
	FOnInputLookAction OnInputLookAction;
	FOnInputCatchAction OnInputCatchAction;
	FOnInputJumpAction OnInputJumpAction;

	FOnInputPauseAction OnInputPauseAction;
	
private:
#pragma region MoveInput
	void MoveReceiveInput(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindMoveInput(UEnhancedInputComponent* EnhancedInputComponent);
	
#pragma endregion

#pragma region LookInput
	void LookReceiveInput(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindLookInput(UEnhancedInputComponent* EnhancedInputComponent);
	
#pragma endregion
	
#pragma region CatchInput
	void CatchReceiveInput(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindCatchInput(UEnhancedInputComponent* EnhancedInputComponent);

#pragma endregion

#pragma region JumpInput
	void JumpReceiveInput(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void BindJumpAction(UEnhancedInputComponent* EnhancedInputComponent);

#pragma endregion

#pragma region QTEInput(Obsolete)
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputQTEAction, float, QTEValue);

	FInputQTEAction OnInputQTEAction;

	void QTEReceiveInput(const FInputActionValue& InputActionValue);
	
	UFUNCTION()
	void BindQTEInputAction(UEnhancedInputComponent* EnhancedInputComponent);
	
	UFUNCTION(BlueprintCallable)
	void ChangeInputMappingContextToQTE();

	UFUNCTION(BlueprintCallable)
	void ChangeInputMappingContextToDefault();
#pragma endregion

#pragma region Pause Action

	void PauseReceiveInput(const FInputActionValue& InputActionValue);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PauseReceiveInputBluePrint(float PauseValue);
	
	UFUNCTION()
	void BindPauseInputAction(UEnhancedInputComponent* EnhancedInputComponent);
	

#pragma endregion
	
};
