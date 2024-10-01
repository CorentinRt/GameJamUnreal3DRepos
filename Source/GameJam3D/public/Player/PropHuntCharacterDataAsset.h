// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PropHuntCharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEJAM3D_API UPropHuntCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catch parameters")
	float CatchLenght;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catch parameters")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Catch parameters")
	float CatchCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random move parameters")
	float MaxRandomMoveStrenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random move parameters")
	float TimeBeforeRandomDirChange;
	
};
