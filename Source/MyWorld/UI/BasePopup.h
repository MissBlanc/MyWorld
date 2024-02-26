// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MyDelegate.h"
#include "CommonEnum.h"
#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "BasePopup.generated.h"

/**
 * 
 */


UCLASS()
class MYWORLD_API UBasePopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UPanelWidget* GP_Title;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TT_Title;

// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
// 		class UBlackBG* BP_BlackBG;

};


UCLASS()
class MYWORLD_API UBasePopup : public UBaseUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	virtual void Open() override;
	virtual void Close() override;
	
	virtual void ShowLayer() override;
	virtual void HideLayer() override;

	virtual EWidgetLayerType GetWidgetLayerType() const override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnOpenImpl();
	UFUNCTION(BlueprintImplementableEvent)
		void OnCloseImpl();

	virtual void OnClickBackButton() override;

	UFUNCTION(BlueprintCallable)
		void OnClick_Close();

	void SetTitleText(FText titleText);

	bool IsShowPopup() { return IsShow; }
	
	bool GetUseMouseRotation() { return UseMouseRotation; }

public:
	MyDelegate::FOnNormalDelegate* GetOnCloseDelegate() { return &OnCloseDelegate; }
private:
	MyDelegate::FOnNormalDelegate OnCloseDelegate;

protected:
	UFUNCTION()
		void OnFinishedAni_Close();

protected:
	UPROPERTY(meta = (BindWidgetOptional))
		class UBasePopupWidget* BP_Common_PopBase;
// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
// 		class UBlackBG* BP_BlackBG;

// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 		FWidgetSound WidgetSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseClickClose = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool UseMouseRotation = false;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
		class UWidgetAnimation* Ani_Close;

	UPROPERTY(meta = (BindWidgetOptional))
	class UBaseButtonWidget* Btn_Close;

	bool IsShow = false;
};
