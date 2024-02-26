// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "FirstPersonMainWidget.generated.h"

/**
 * 
 */

UCLASS()
class MYWORLD_API UFirstPersonMainWidget : public UBaseMainWidget
{
	GENERATED_BODY()
protected:
 	virtual void NativeOnInitialized() override;

protected:
 	void OnClickGotoTitle();

	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_GotoTitle;
};
