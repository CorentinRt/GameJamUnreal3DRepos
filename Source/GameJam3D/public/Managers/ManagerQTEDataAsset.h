// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ManagerQTEDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEJAM3D_API UManagerQTEDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Parameters")
	float QTEDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Parameters")
	float ScaleTimeQTE;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QTE Parameters")
	float InvincibilityCooldownQTE;
};
