// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseButtonWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/AudioComponent.h"
#include "Components/Image.h"

void UBaseButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (IsValid(TT_Text) &&
		!LocalKey.IsEmpty())
		TT_Text->SetText(FText::FromString(LocalKey));
}

void UBaseButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(TT_Text) &&
		!LocalKey.IsEmpty())
		TT_Text->SetText(FText::FromString(LocalKey));

	//Btn_Click->LongPressTime = LongPressTime;
}

void UBaseButtonWidget::BeginDestroy()
{
	StopClickSound();

	Super::BeginDestroy();
}



//
// Sound
void UBaseButtonWidget::OnClickedButton()
{
	if (!Enabled)
		return;

	PlayClickSound();

	if (ClickDelegate.IsBound())
	{
		ClickDelegate.Execute();
	}
}

void UBaseButtonWidget::OnPressedButton()
{
	if (!Enabled)
		return;

	if (PressedDelegate.IsBound())
	{
		PressedDelegate.Execute();
	}
}

void UBaseButtonWidget::OnReleasedButton()
{
	if (!Enabled)
		return;

	if (ReleasedDelegate.IsBound())
	{
		ReleasedDelegate.Execute();
	}
}

void UBaseButtonWidget::OnLongPressedButton()
{
	if (!Enabled)
		return;

	if (LongPressedDelegate.IsBound())
	{
		LongPressedDelegate.Execute();
	}
}

void UBaseButtonWidget::PlayClickSound()
{
	if (ClickSoundList.IsEmpty())
		return;

	for (auto& sound : ClickSoundList)
	{
		TObjectPtr< UAudioComponent > soundAsset = UGameplayStatics::SpawnSound2D(GetWorld(), sound);
		if (soundAsset == nullptr)
			continue;

		UsedClickSoundList.Add(soundAsset);
	}
}

void UBaseButtonWidget::StopClickSound()
{
	if (UsedClickSoundList.Num() == 0)
		return;

	for (int32 i = 0; i < UsedClickSoundList.Num(); ++i)
	{
		if (UsedClickSoundList[i] == nullptr)
			continue;

		UsedClickSoundList[i]->Stop();
	}

	UsedClickSoundList.Empty();
}




//
// Text
void UBaseButtonWidget::SetText(FString localKey)
{
	if (TT_Text)
		TT_Text->SetText(FText::FromString(localKey));
}

void UBaseButtonWidget::SetText(FText text)
{
	if (TT_Text)
		TT_Text->SetText(text);
}




//
// Enable / Disable (실제로 클릭을 할 수 있는가 여부, 버튼 제어)
void UBaseButtonWidget::SetEnable(bool enable)
{
	Enabled = enable;

	if (Img_Disable)
		Img_Disable->SetVisibility(enable ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}



//
// Active / Inactive (이 버튼으로 인한 기능이 활성화 되어 있는 지 여부, 비주얼적인 처리만 담당)
void UBaseButtonWidget::SetActive(bool active)
{
	if (IsActive == active)
		return;

	IsActive = active;

	OnActive(IsActive);
}