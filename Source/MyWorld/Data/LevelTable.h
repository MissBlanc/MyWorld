// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelTable.generated.h"

/**
 * 
 */

USTRUCT()
struct MYWORLD_API FLevelData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, DisplayName = "ID", Category = "Level")
	int32 Id = 0;
	UPROPERTY(EditAnywhere, DisplayName = "RESOURCE", Category = "Level")
	FString Resource;
};

UCLASS(BlueprintType, Const)
class MYWORLD_API ULevelTable : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "LEVEL", Category = "리스트")
	TMap<int32/*Id*/, FString/*Resource*/> Data;
};
