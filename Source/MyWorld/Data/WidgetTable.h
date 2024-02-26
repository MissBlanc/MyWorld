// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CommonEnum.h"
#include "WidgetTable.generated.h"

/**
 * 
 */

class UBaseUserWidget;

USTRUCT()
struct MYWORLD_API FWidgetData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, DisplayName = "위젯", Category = "위젯 데이터")
		TSubclassOf<UBaseUserWidget> WidgetObject = nullptr;
};


UCLASS(BlueprintType, Const)
class MYWORLD_API UWidgetTable : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, DisplayName = "위젯", Category = "리스트")
		TMap<EWidgetType, FWidgetData> Data;
};
