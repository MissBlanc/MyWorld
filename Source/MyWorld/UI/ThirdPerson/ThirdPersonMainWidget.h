// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "ThirdPersonMainWidget.generated.h"

/**
 * 
 */

UCLASS()
class MYWORLD_API UThirdPersonMainWidget : public UBaseMainWidget
{
	GENERATED_BODY()
protected:
 	virtual void NativeOnInitialized() override;

protected:
 	void OnClickGotoTitle();

	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_GotoTitle;
};
