// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "BaseMainWidget.generated.h"

/**
 * 
 */

UCLASS()
class MYWORLD_API UBaseMainWidget : public UBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	virtual void Open() override;
	virtual void Close() override;

private:
	bool IsInit = false;
};
