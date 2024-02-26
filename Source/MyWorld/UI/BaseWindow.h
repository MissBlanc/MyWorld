// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"

#include "Delegates/DelegateCombinations.h"
#include "CommonEnum.h"
#include "BaseUserWidget.h"
#include "BaseWindow.generated.h"

/**
 * 
 */

enum class ECurrencyType;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOaseWindowDelegate);

UCLASS()
class MYWORLD_API UBaseWindow : public UBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	virtual void Open() override;
	virtual void Close() override;

	virtual void ShowLayer() override;
	virtual void HideLayer() override;

	virtual void InitPageText(FText text);
	virtual void InitPageText(FString localKey);

	virtual void ShowBackButton(bool visible);

	void ClearCurrencyWidget();
	void InitCurrency(const TArray<ECurrencyType>& currencyTypes);
	void SetCurrencyVisible(ECurrencyType currencyType, bool visible);
	
	virtual void OnClickBackButton() override;

	virtual EWidgetLayerType GetWidgetLayerType() const override;
	
	FOaseWindowDelegate* GetOnWindowHideDelegate() { return &OnWindowHideDelegate; }

protected:
	UPROPERTY(meta = (BindWidget))
	class UBaseButtonWidget* Btn_Close;

private:
	FOaseWindowDelegate OnWindowHideDelegate;
};



