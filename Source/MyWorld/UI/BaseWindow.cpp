// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWindow.h"
#include "UILayer.h"
#include "BaseHUD.h"
#include "BaseButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Components/AudioComponent.h"

void UBaseWindow::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(Btn_Close))
	{
		Btn_Close->GetClickDelegate().Unbind();
		Btn_Close->GetClickDelegate().BindUObject(this, &UBaseWindow::Close);
	}
}

void UBaseWindow::NativeConstruct()
{
	Super::NativeConstruct();

// 	if (IsValid(BP_Common_Window))
// 	{
// 		BP_Common_Window->BP_Common_Top->GetExitDelegate()->BindUObject(this, &UBaseWindow::Close);
// 		BP_Common_Window->BP_Common_Top->GetBackDelegate()->BindUObject(this, &UBaseWindow::OnClickBackButton);
// 	}
// 
// 	WidgetSound.InitSound();
}

void UBaseWindow::NativeDestruct()
{
	//WidgetSound.ResetSound();
	Super::NativeDestruct();
}

void UBaseWindow::Open()
{
	ABaseHUD* hud = ABaseHUD::Get();
	if (IsValid(hud) && hud->IsInLayer(this))
		return;

	Super::Open();
	
	AddWidgetToLayer();
	ShowLayer();

 	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
 	if (IsValid(playerController))
 	{
 		playerController->SetIgnoreMoveInput(true);
 		playerController->SetIgnoreLookInput(true);
 
 		/*APlayerController* PlayerController = Cast<APlayerController>(playerController);
 		if (IsValid(PlayerController))
 			PlayerController->DisableTouchInterface();*/
 	}
}

void UBaseWindow::Close()
{
	ABaseHUD* hud = ABaseHUD::Get();
	if (IsValid(hud) && !hud->IsInLayer(this))
		return;

	Super::Close();

	if(OnWindowHideDelegate.IsBound())
		OnWindowHideDelegate.Broadcast();

 	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
 	if (IsValid(playerController))
 	{
 		playerController->SetIgnoreMoveInput(false);
 		playerController->SetIgnoreLookInput(false);
 
 		/*APlayerController* PlayerController = Cast<APlayerController>(playerController);
 		if (IsValid(PlayerController))
 			PlayerController->ReleaseTouchInterface();*/
 	}

	HideLayer();
	RemoveWidgetFromLayer();
}

void UBaseWindow::ShowLayer()
{
	Super::ShowLayer();
	
}

void UBaseWindow::HideLayer()
{
	Super::HideLayer();

}

void UBaseWindow::InitPageText(FText text)
{
// 	if (IsValid(BP_Common_Window))
// 	{
// 		BP_Common_Window->BP_Common_Top->InitPageText(text);
// 	}
}

void UBaseWindow::InitPageText(FString localKey)
{
// 	if (IsValid(BP_Common_Window))
// 	{
// 		BP_Common_Window->BP_Common_Top->InitPageText(localKey);
// 	}
}

void UBaseWindow::ShowBackButton(bool visible)
{
// 	if (IsValid(BP_Common_Window) && IsValid(BP_Common_Window->BP_Common_Top))
// 	{
// 		BP_Common_Window->BP_Common_Top->SetBackButtonVisible(visible);
// 	}
}

void UBaseWindow::ClearCurrencyWidget()
{
// 	if (IsValid(BP_Common_Window) && IsValid(BP_Common_Window->BP_Common_Top))
// 	{
// 		BP_Common_Window->BP_Common_Top->ClearCurrencyWidget();
// 	}
}

void UBaseWindow::InitCurrency(const TArray<ECurrencyType>& currencyTypes)
{
// 	if (IsValid(BP_Common_Window) && IsValid(BP_Common_Window->BP_Common_Top))
// 	{
// 		BP_Common_Window->BP_Common_Top->InitCurrencyWidget(currencyTypes);
// 	}
}

void UBaseWindow::SetCurrencyVisible(ECurrencyType currencyType, bool visible)
{
// 	if (IsValid(BP_Common_Window) && IsValid(BP_Common_Window->BP_Common_Top))
// 	{
// 		BP_Common_Window->BP_Common_Top->SetCurrencyVisible(currencyType, visible);
// 	}
}

void UBaseWindow::OnClickBackButton()
{
	Close();
}

EWidgetLayerType UBaseWindow::GetWidgetLayerType() const
{
	return ForceLayerType != EWidgetLayerType::None ? ForceLayerType : EWidgetLayerType::Window;
}
