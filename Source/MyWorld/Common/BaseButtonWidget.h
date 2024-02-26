// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "MyDelegate.h"
#include "BaseButtonWidget.generated.h"

/**
 * 
 */

UCLASS()
class MYWORLD_API UBaseButtonWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;

	//
	// Button
	MyDelegate::FOnNormalDelegate& GetClickDelegate() { return ClickDelegate; }
	MyDelegate::FOnNormalDelegate& GetPressedDelegate() { return PressedDelegate; }
	MyDelegate::FOnNormalDelegate& GetReleasedDelegate() { return ReleasedDelegate; }
	MyDelegate::FOnNormalDelegate& GetLongPressedDelegate() { return LongPressedDelegate; }

protected:
	UFUNCTION(BlueprintCallable)
		void OnClickedButton();

	UFUNCTION(BlueprintCallable)
		void OnPressedButton();

	UFUNCTION(BlueprintCallable)
		void OnReleasedButton();

	UFUNCTION(BlueprintCallable)
		void OnLongPressedButton();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
		float LongPressTime = 1.f;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Custom")
		class UButton* Btn_Click;

	//
	// Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Button Sound")
		TArray< class USoundBase* > ClickSoundList;

	UPROPERTY(Transient)
		TArray<TObjectPtr<class UAudioComponent>> UsedClickSoundList;

	void PlayClickSound();
	void StopClickSound();

	//
	// Text
public:
	void SetText(FString localKey);
	void SetText(FText text);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
		FString LocalKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetOptional))
		class UTextBlock* TT_Text;

	//
	// Enable / Disable (실제로 클릭을 할 수 있는가 여부, 버튼 제어)
public:
	void SetEnable(bool enable);
	bool GetEnable() const { return Enabled; }
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
		class UImage* Img_Disable;

	bool Enabled = true;

	//
	// Active / Inactive (이 버튼으로 인한 기능이 활성화 되어 있는 지 여부, 비주얼적인 처리만 담당)
public:
	void SetActive(bool active);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
		class UImage* Img_Inactive;

	UFUNCTION(BlueprintImplementableEvent)
		void OnActive(bool active);

protected:
	bool IsActive = false;


private:
	MyDelegate::FOnNormalDelegate ClickDelegate;
	MyDelegate::FOnNormalDelegate PressedDelegate;
	MyDelegate::FOnNormalDelegate ReleasedDelegate;
	MyDelegate::FOnNormalDelegate LongPressedDelegate;
};
