// Fill out your copyright notice in the Description page of Project Settings.
#include "FirstPersonMainWidget.h"
#include "../Common/MyGameInstance.h"
#include "../../Common/BaseButtonWidget.h"
 
 void UFirstPersonMainWidget::NativeOnInitialized()
 {
 	Super::NativeOnInitialized();
 
 	if (IsValid(Btn_GotoTitle))
 	{
        Btn_GotoTitle->GetClickDelegate().Unbind();
        Btn_GotoTitle->GetClickDelegate().BindUObject(this, &UFirstPersonMainWidget::OnClickGotoTitle);
 	}
 }
 
 void UFirstPersonMainWidget::OnClickGotoTitle()
 {
	 UMyGameInstance* gameInstance = UMyGameInstance::Get();
	 if (!IsValid(gameInstance))
		 return;

	 gameInstance->GotoLevel(101);
 }