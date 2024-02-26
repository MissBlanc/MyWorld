// Fill out your copyright notice in the Description page of Project Settings.
#include "TitleMainWidget.h"
#include "BaseHUD.h"
#include "BaseWindow.h"
#include "BaseButtonWidget.h"
#include "BasePopup.h"
#include "MyGameInstance.h"

void UTitleMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(Btn_TestWindow))
	{
		Btn_TestWindow->GetClickDelegate().Unbind();
		Btn_TestWindow->GetClickDelegate().BindUObject(this, &UTitleMainWidget::OnClickTestWindow);
	}

	if (IsValid(Btn_TestPopup))
	{
		Btn_TestPopup->GetClickDelegate().Unbind();
		Btn_TestPopup->GetClickDelegate().BindUObject(this, &UTitleMainWidget::OnClickTestPopup);
	}

	if (IsValid(Btn_MoveDemo1))
	{
		Btn_MoveDemo1->GetClickDelegate().Unbind();
		Btn_MoveDemo1->GetClickDelegate().BindUObject(this, &UTitleMainWidget::OnClickMoveDemo1);
	}

	if (IsValid(Btn_MoveDemo2))
	{
		Btn_MoveDemo2->GetClickDelegate().Unbind();
		Btn_MoveDemo2->GetClickDelegate().BindUObject(this, &UTitleMainWidget::OnClickMoveDemo2);
	}
}

void UTitleMainWidget::OnClickTestWindow()
{
	ABaseHUD* hud = ABaseHUD::Get();
	if (!IsValid(hud))
		return;

	UBaseWindow* window = Cast<UBaseWindow>(hud->GetWidget(EWidgetType::BasicTestWindow));
	if (!IsValid(window))
		return;

	window->Open();
}

void UTitleMainWidget::OnClickTestPopup()
{
	ABaseHUD* hud = ABaseHUD::Get();
	if (!IsValid(hud))
		return;

	UBasePopup* popup = Cast<UBasePopup>(hud->GetWidget(EWidgetType::BasicTestPopup1));
	if (!IsValid(popup))
		return;

	popup->Open();
}

void UTitleMainWidget::OnClickMoveDemo1()
{
	UMyGameInstance* gameInstance = UMyGameInstance::Get();
	if (!IsValid(gameInstance))
		return;

	gameInstance->GotoLevel(102);
}

void UTitleMainWidget::OnClickMoveDemo2()
{
	UMyGameInstance* gameInstance = UMyGameInstance::Get();
	if (!IsValid(gameInstance))
		return;

	gameInstance->GotoLevel(103);
}
