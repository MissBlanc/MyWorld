// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyDelegate.h"
#include "BaseUserWidget.generated.h"

/**
 *
 */

enum class EWidgetType : uint8;
enum class EWidgetLayerType : uint8;

UCLASS()
class MYWORLD_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UBaseUserWidget(const FObjectInitializer& ObjectInitializer);

public:
	int32 GetZorder() { return Zorder; }
	void SetZorder(int32 order) { Zorder = order; }

	int32 GetOriginZorder()
	{
		if (OriginZorder < 0)
			OriginZorder = Zorder;
		return OriginZorder;
	}

	MyDelegate::FOnNormalDelegate& GetCloseDelegate() { return CloseDelegate; }

	void AddWidgetToLayer();
	void RemoveWidgetFromLayer();

	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	void SetVisibilityForce(ESlateVisibility InVisibility);

	void Refresh();

	bool IsInViewportPosition() const;

	virtual void OnClickBackButton() {};
	virtual void Open();				// UI Layer Panel�� �߰��� �� ȣ��
	virtual void Close();				// UI Layer Panel���� ������ �� ȣ��

	virtual void ShowLayer();			// UI Layer Panel���� ������ ���� Ȱ��ȭ�� �� ȣ��
	virtual void HideLayer();			// UI Layer Panel���� ������ ���� ��Ȱ��ȭ�� �� ȣ��

protected:
	// ����
	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnimOptional))
	class UWidgetAnimation* Ani_Show;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Zorder = 0;

	int32 OriginZorder = -1;

	float LastTickTime;

private:
	MyDelegate::FOnNormalDelegate CloseDelegate;

	bool InitVisibility = false;
	ESlateVisibility CurrentVisiblity;

public:
	virtual EWidgetLayerType GetWidgetLayerType() const;
protected:
	EWidgetType WidgetType;
	EWidgetLayerType WidgetLayerType;			// WidgetTable���� ������ ���̾�Ÿ��
	EWidgetLayerType ForceLayerType;			// ��Ȳ�� ���� ������ �� �ִ� ���̾� Ÿ��
};
