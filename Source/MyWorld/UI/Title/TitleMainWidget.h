// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "TitleMainWidget.generated.h"

/**
 * 
 */

UCLASS()
class MYWORLD_API UTitleMainWidget : public UBaseMainWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

private:
	bool IsInit = false;


protected:
	void OnClickTestWindow();
	void OnClickTestPopup();
	void OnClickMoveDemo1();
	void OnClickMoveDemo2();

	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_TestWindow;
	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_TestPopup;
	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_MoveDemo1;
	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_MoveDemo2;
};
