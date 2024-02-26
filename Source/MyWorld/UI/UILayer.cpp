// Fill out your copyright notice in the Description page of Project Settings.
#include "UILayer.h"

#include "Components/PanelWidget.h"
#include "Components/GridSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "BaseHUD.h"

void FLayerInfo::AddChild(UBaseUserWidget* widget)
{
	if (!ParentPanel.IsValid())
		return;
	if (WidgetContainer.Contains(widget))
		return;

	ParentPanel->AddChild(widget);

	TopWidget = widget;
	WidgetContainer.Emplace(widget);

	UGridSlot* gridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(widget);
	if (IsValid(gridSlot))
	{
		gridSlot->SetLayer(++CurrentLayer);
	}
}

void FLayerInfo::RemoveChild(UBaseUserWidget* widget)
{
	if (!ParentPanel.IsValid())
		return;
	if (!WidgetContainer.Contains(widget))
		return;

	ParentPanel->RemoveChild(widget);
	WidgetContainer.Remove(widget);
	
	TWeakObjectPtr<UBaseUserWidget> newTopWidget = !WidgetContainer.IsEmpty() ? WidgetContainer[WidgetContainer.Num() - 1] : nullptr;
	if (TopWidget.Get() != newTopWidget.Get())
	{
		TopWidget = newTopWidget;
	}

	UpdateCurrentLayer();
}

void FLayerInfo::RemoveChildAll(UBaseUserWidget* exceptWidget /*= nullptr*/)
{
	TArray<TWeakObjectPtr<UBaseUserWidget>> removeWidgetList;

	for (int32 i = WidgetContainer.Num() - 1; i >= 0; --i)
	{
		if (WidgetContainer[i].Get() == exceptWidget)
			continue;

		removeWidgetList.Emplace(WidgetContainer[i].Get());
	}

	for (auto iter = removeWidgetList.CreateIterator(); iter; ++iter)
	{
		(*iter)->Close();
	}

	TWeakObjectPtr<UBaseUserWidget> newTopWidget = !WidgetContainer.IsEmpty() ? WidgetContainer[WidgetContainer.Num() - 1] : nullptr;
	if (TopWidget.Get() != newTopWidget.Get())
	{
		TopWidget = newTopWidget;
	}

	UpdateCurrentLayer();
}

void FLayerInfo::Clear()
{
	while (WidgetContainer.Num() > 0)
	{
		ParentPanel->RemoveChild(WidgetContainer[0].Get());
		WidgetContainer.RemoveAt(0);
	}

	TopWidget = nullptr;

	UpdateCurrentLayer();
}

void FLayerInfo::UpdateCurrentLayer()
{
	UGridSlot* gridSlot = nullptr;
	if (TopWidget.IsValid())
		gridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(TopWidget.Get());

	if (IsValid(gridSlot))
	{
		CurrentLayer = gridSlot->GetLayer();
	}
	else
	{
		CurrentLayer = -1;
	}
}

int32 FLayerInfo::GetChildNum()
{
	return WidgetContainer.Num();
}

UPanelWidget* FLayerInfo::GetParentPanel()
{
	if (ParentPanel.IsValid())
		return ParentPanel.Get();
	return nullptr;
}

UBaseUserWidget* FLayerInfo::GetTopWidget()
{
	if (TopWidget.IsValid())
		return TopWidget.Get();
	return nullptr;
}


void UMainHudLayerInfo::AddChild(UBaseUserWidget* widget)
{
	if (WidgetContainer.Contains(widget))
		return;

	if (TopWidget.IsValid())
		TopWidget->HideLayer();
	
	FLayerInfo::AddChild(widget);
}

void UMainHudLayerInfo::RemoveChild(UBaseUserWidget* widget)
{
	FLayerInfo::RemoveChild(widget);

	if (TopWidget.IsValid())
		TopWidget->ShowLayer();
}











UUILayer* UUILayer::Get()
{
	ABaseHUD* hud = ABaseHUD::Get();
	if (!IsValid(hud))
		return nullptr;

	return hud->GetUILayer();
}

void UUILayer::NativeConstruct()
{
// #if ENABLE_DRAW_DEBUG	
// 	ANBPlayerController* playerController = ANBPlayerController::Get();
// 	if (IsValid(playerController) && IsValid(playerController->GetCheatManager()) && playerController->GetCheatManager()->CheckDebugUILayer())
// 	{
// 		NB_LOG(NBLOG, Log, TEXT("[HUD] HudName:%s NativeConstruct()"), *GetName());
// 	}
// #endif
}

void UUILayer::NativeDestruct()
{
	Super::NativeDestruct();
	
// #if ENABLE_DRAW_DEBUG	
// 	ANBPlayerController* playerController = ANBPlayerController::Get();
// 	if (IsValid(playerController) && IsValid(playerController->GetCheatManager()) && playerController->GetCheatManager()->CheckDebugUILayer())
// 	{
// 		NB_LOG(NBLOG, Log, TEXT("[HUD] HudName:%s NativeDestruct()"), *GetName());
// 	}
// #endif
	
	for (auto iter = LayerInfoContainer.CreateIterator(); iter; ++iter)
	{
		if (!iter.Value().IsValid())
			continue;
		iter.Value()->Clear();
	}

	LayerInfoContainer.Empty();
}

void UUILayer::RemoveFromParent()
{
	Super::RemoveFromParent();

// #if ENABLE_DRAW_DEBUG	
// 	ANBPlayerController* playerController = ANBPlayerController::Get();
// 	if (IsValid(playerController) && IsValid(playerController->GetCheatManager()) && playerController->GetCheatManager()->CheckDebugUILayer())
// 	{
// 		NB_LOG(NBLOG, Log, TEXT("[HUD] HudName:%s RemoveFromParent()"), *GetName());
// 	}
// #endif
}

void UUILayer::InitLayerInfo()
{
	AddToViewport();

	LayerInfoContainer.Empty();
	LayerInfoContainer.Emplace(EWidgetLayerType::MainHud, MakeShareable(new UMainHudLayerInfo(EWidgetLayerType::MainHud, GP_MainHud)));
	LayerInfoContainer.Emplace(EWidgetLayerType::Window, MakeShareable(new UMainHudLayerInfo(EWidgetLayerType::Window, GP_Window)));
	LayerInfoContainer.Emplace(EWidgetLayerType::Popup, MakeShareable(new FLayerInfo(EWidgetLayerType::Popup, GP_Popup)));
	LayerInfoContainer.Emplace(EWidgetLayerType::Sequence, MakeShareable(new FLayerInfo(EWidgetLayerType::Sequence, GP_Sequence)));
	LayerInfoContainer.Emplace(EWidgetLayerType::System, MakeShareable(new FLayerInfo(EWidgetLayerType::System, GP_System)));
}

void UUILayer::AddWidget(EWidgetLayerType layerType, UBaseUserWidget* widget)
{
	if (!LayerInfoContainer.Contains(layerType))
		return;
	if (!IsValid(widget))
		return;

	TSharedPtr<FLayerInfo> layerInfo = LayerInfoContainer[layerType];
	if (!layerInfo.IsValid())
		return;

	layerInfo->AddChild(widget);

// #if ENABLE_DRAW_DEBUG	
// 	ANBPlayerController* playerController = ANBPlayerController::Get();
// 	if (IsValid(playerController) && IsValid(playerController->GetCheatManager()) && playerController->GetCheatManager()->CheckDebugUILayer())
// 	{
// 		NB_LOG(NBLOG, Log, TEXT("[HUD] layerType:%d HudName:%s AddWidget()"), layerType, *widget->GetName());
// 	}
// #endif
}

void UUILayer::RemoveWidget(EWidgetLayerType layerType, UBaseUserWidget* widget)
{
	if (!LayerInfoContainer.Contains(layerType))
		return;

	TSharedPtr<FLayerInfo> layerInfo = LayerInfoContainer[layerType];
	if (!layerInfo.IsValid())
		return;

	layerInfo->RemoveChild(widget);

// #if ENABLE_DRAW_DEBUG	
// 	ANBPlayerController* playerController = ANBPlayerController::Get();
// 	if (IsValid(playerController) && IsValid(playerController->GetCheatManager()) && playerController->GetCheatManager()->CheckDebugUILayer())
// 	{
// 		NB_LOG(NBLOG, Log, TEXT("[HUD] layerType:%d HudName:%s RemoveWidget()"), layerType, *widget->GetName());
// 	}
// #endif
}

void UUILayer::SetVisibleLayer(bool visible, EWidgetLayerType layerType /*= EWidgetLayerType::None*/)
{
	for (auto iter = LayerInfoContainer.CreateIterator(); iter; ++iter)
	{
		if (layerType != EWidgetLayerType::None && iter.Key() != layerType)
			continue;

		TSharedPtr<FLayerInfo>& layerInfo = iter.Value();
		if (!layerInfo.IsValid())
			continue;
		
		if (!IsValid(layerInfo->GetParentPanel()))
			continue;

		layerInfo->GetParentPanel()->SetVisibility(visible ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
		
		UBaseUserWidget* topWidget = layerInfo->GetTopWidget();
		if (IsValid(topWidget))
		{
			if (visible)
				topWidget->ShowLayer();
			else
				topWidget->HideLayer();
		}
	}
}

bool UUILayer::IsInLayer(UBaseUserWidget* widget) const
{
	if (!IsValid(widget))
		return false;
	if (!LayerInfoContainer.Contains(widget->GetWidgetLayerType()))
		return false;

	return LayerInfoContainer[widget->GetWidgetLayerType()]->GetParentPanel() == widget->GetParent();
}

int32 UUILayer::GetLayerWidgetNum(EWidgetLayerType layerType)
{
	if (!LayerInfoContainer.Contains(layerType))
		return -1;
	if (!LayerInfoContainer[layerType].IsValid())
		return -1;
	return LayerInfoContainer[layerType]->GetChildNum();
}

FLayerInfo* UUILayer::GetLayerInfo(EWidgetLayerType layerType)
{
	if (!LayerInfoContainer.Contains(layerType))
		return nullptr;
	if (!LayerInfoContainer[layerType].IsValid())
		return nullptr;
	return LayerInfoContainer[layerType].Get();
}

UBaseUserWidget* UUILayer::GetTopWidget()
{
	UBaseUserWidget* topWidget = nullptr;

	const UEnum* enumPtr = StaticEnum<EWidgetLayerType>();
	if (!enumPtr)
		return topWidget;

	const int32 len = enumPtr->NumEnums();
	for (int i = enumPtr->NumEnums() - 1; i >= 0; --i)
	{
		const EWidgetLayerType enumValue = (EWidgetLayerType)(enumPtr->GetValueByIndex(i));
		if (!LayerInfoContainer.Contains(enumValue))
			continue;
	
		topWidget = LayerInfoContainer[enumValue]->GetTopWidget();

		if (IsValid(topWidget))
			break;
	}

	return topWidget;
}



