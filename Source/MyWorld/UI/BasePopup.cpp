// Fill out your copyright notice in the Description page of Project Settings.
#include "BasePopup.h"
#include "Components/GridPanel.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "BaseHUD.h"
#include "BaseButtonWidget.h"
#include "Kismet/GameplayStatics.h"

void UBasePopup::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IsValid(Btn_Close))
	{
		Btn_Close->GetClickDelegate().Unbind();
		Btn_Close->GetClickDelegate().BindUObject(this, &UBasePopup::Close);
	}
}

void UBasePopup::NativeConstruct()
{
	Super::NativeConstruct();

// 	if (IsValid(BP_Common_PopBase))
// 	{
// 		BP_Common_PopBase->BP_BlackBG->GetClickDelegate().Unbind();
// 		BP_Common_PopBase->BP_BlackBG->GetClickDelegate().BindUObject(this, &UBasePopup::OnClick_Close);
// 	}

// 	if (IsValid(BP_BlackBG))
// 	{
// 		BP_BlackBG->GetClickDelegate().Unbind();
// 		BP_BlackBG->GetClickDelegate().BindUObject(this, &UBasePopup::OnClick_Close);
// 	}

	if (IsValid(Ani_Close))
	{
		UnbindAllFromAnimationFinished(Ani_Close);

		FWidgetAnimationDynamicEvent finishedEvent;
		finishedEvent.BindDynamic(this, &UBasePopup::OnFinishedAni_Close);
		BindToAnimationFinished(Ani_Close, finishedEvent);
	}
}

void UBasePopup::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBasePopup::Open()
{
	if (IsShow)
		return;

	ABaseHUD* hud = ABaseHUD::Get();
	if (IsValid(hud) && hud->IsInLayer(this))
		return;

	AddWidgetToLayer();
	ShowLayer();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(playerController))
	{
		playerController->SetIgnoreMoveInput(true);
		playerController->SetIgnoreLookInput(true);
	}

	if (IsValid(Ani_Show) &&
		!IsAnimationPlaying(Ani_Show))
	{
		PlayAnimation(Ani_Show);
	}

	if (IsValid(hud))
	{
// 		UBaseMainWidget* mainWidget = hud->GetMainWidget<UBaseMainWidget>();
// 		if (IsValid(mainWidget))
// 			mainWidget->OnOpenPopup(this);
	}

	OnOpenImpl();
}

void UBasePopup::Close()
{
	if (IsAnimationPlaying(Ani_Close))
		return;

	ABaseHUD* hud = ABaseHUD::Get();
	if (IsValid(hud) && !hud->IsInLayer(this))
		return;

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(playerController))
	{
		playerController->SetIgnoreMoveInput(false);
		playerController->SetIgnoreLookInput(false);
	}

	//WidgetSound.PlayCloseSound();

	if (IsValid(Ani_Close))
	{
		PlayAnimation(Ani_Close);
	}
	else
	{
		OnFinishedAni_Close();
	}

	OnCloseImpl();
}

void UBasePopup::ShowLayer()
{
	Super::ShowLayer();

	IsShow = true;
}

void UBasePopup::HideLayer()
{
	IsShow = false;

	Super::HideLayer();
}

EWidgetLayerType UBasePopup::GetWidgetLayerType() const
{
	return ForceLayerType != EWidgetLayerType::None ? ForceLayerType : EWidgetLayerType::Popup;
}

void UBasePopup::OnClickBackButton()
{
	OnClick_Close();
}

void UBasePopup::OnClick_Close()
{
	if (!UseClickClose)
		return;

	Close();
}

void UBasePopup::SetTitleText(FText titleText)
{
	if (IsValid(BP_Common_PopBase) &&
		IsValid(BP_Common_PopBase->GP_Title) &&
		IsValid(BP_Common_PopBase->TT_Title))
	{
		BP_Common_PopBase->GP_Title->SetVisibility(!titleText.IsEmpty() ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
		BP_Common_PopBase->TT_Title->SetText(titleText);
	}
}

void UBasePopup::OnFinishedAni_Close()
{
	OnCloseDelegate.ExecuteIfBound();

	HideLayer();
	RemoveWidgetFromLayer();
}