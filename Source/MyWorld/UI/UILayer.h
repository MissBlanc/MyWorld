// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "CommonEnum.h"
#include "Components/PanelWidget.h"
#include "UILayer.generated.h"

/**
 * 
 */

class MYWORLD_API FLayerInfo
{
public:
	FLayerInfo() {}
	FLayerInfo(EWidgetLayerType layerType, class UPanelWidget* parentPanel)
		:LayerType(layerType)
	{
		ParentPanel = parentPanel;
	}
	virtual ~FLayerInfo(){}

	virtual void AddChild(UBaseUserWidget* widget);
	virtual void RemoveChild(UBaseUserWidget* widget);
	virtual void RemoveChildAll(UBaseUserWidget* exceptWidget = nullptr);

	void Clear();

protected:
	void UpdateCurrentLayer();

public:
	int32 GetChildNum();
	UPanelWidget* GetParentPanel();
	UBaseUserWidget* GetTopWidget();

protected:
	EWidgetLayerType LayerType;
	TWeakObjectPtr<class UPanelWidget> ParentPanel;
	TWeakObjectPtr<UBaseUserWidget> TopWidget;
	int32 CurrentLayer = -1;

	TArray<TWeakObjectPtr<UBaseUserWidget>> WidgetContainer;
};

class MYWORLD_API UMainHudLayerInfo : public FLayerInfo
{
public:
	UMainHudLayerInfo(EWidgetLayerType layerType, class UPanelWidget* parentPanel)
		: FLayerInfo(layerType, parentPanel)
	{
	}

	virtual void AddChild(UBaseUserWidget* widget) override;
	virtual void RemoveChild(UBaseUserWidget* widget) override;
};


UCLASS()
class MYWORLD_API UUILayer : public UBaseUserWidget
{
	GENERATED_BODY()
public:
	static UUILayer* Get();
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public:
	virtual void RemoveFromParent() override;

public:
	void InitLayerInfo();

	void AddWidget(EWidgetLayerType layerType, UBaseUserWidget* widget);
	void RemoveWidget(EWidgetLayerType layerType, UBaseUserWidget* widget);

	void SetVisibleLayer(bool visible, EWidgetLayerType layerType = EWidgetLayerType::None);

	bool IsInLayer(UBaseUserWidget* widget) const;

public:
	int32 GetLayerWidgetNum(EWidgetLayerType layerType);
	FLayerInfo* GetLayerInfo(EWidgetLayerType layerType);
	UBaseUserWidget* GetTopWidget();

 protected:
	 UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 class UPanelWidget* GP_MainHud;
	 UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 class UPanelWidget* GP_Window;
	 UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 class UPanelWidget* GP_Popup;
	 UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 class UPanelWidget* GP_Sequence;
	 UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	 class UPanelWidget* GP_System;
 
	TMap<EWidgetLayerType, TSharedPtr<FLayerInfo>> LayerInfoContainer;
};
