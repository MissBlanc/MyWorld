// Fill out your copyright notice in the Description page of Project Settings.
#include "ThirdPersonMainWidget.h"
#include "../Common/MyGameInstance.h"
#include "../../Common/BaseButtonWidget.h"
 
 void UThirdPersonMainWidget::NativeOnInitialized()
 {
 	Super::NativeOnInitialized();
 
 	if (IsValid(Btn_GotoTitle))
 	{
        Btn_GotoTitle->GetClickDelegate().Unbind();
        Btn_GotoTitle->GetClickDelegate().BindUObject(this, &UThirdPersonMainWidget::OnClickGotoTitle);
 	}
 }
 
 void UThirdPersonMainWidget::OnClickGotoTitle()
 {
	 UMyGameInstance* gameInstance = UMyGameInstance::Get();
	 if (!IsValid(gameInstance))
		 return;

	 gameInstance->GotoLevel(101);
 }