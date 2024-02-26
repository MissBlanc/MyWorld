// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseMainWidget.h"
#include "BaseHUD.h"
#include "BaseWindow.h"
#include "BaseButtonWidget.h"
#include "BasePopup.h"
#include "MyGameInstance.h"

void UBaseMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UBaseMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UBaseMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseMainWidget::Open()
{
	Super::Open();

	AddWidgetToLayer();
}

void UBaseMainWidget::Close()
{
	Super::Close();

	RemoveWidgetFromLayer();
}