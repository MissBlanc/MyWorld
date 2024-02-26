// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CommonEnum.h"
#include <BaseUserWidget.h>
#include "BaseHUD.generated.h"

/**
 *
 */

class UWidgetTable;
enum class EWidgetType : uint8;

USTRUCT()
struct FWidgetVisibleInfo
{
	GENERATED_BODY()

public:
	int32 HiddenStack = 0;
	int32 DimmedStack = 0;

	ESlateVisibility ShowVisibilityType;
};

UCLASS()
class MYWORLD_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void DrawHUD() override;
	virtual void Tick(float DeltaTime) override;

public:
	static ABaseHUD* Get();

	ABaseHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void InitializeHud();

	

	bool IsInLayer(UBaseUserWidget* widget) const;
	void AddToLayer(UBaseUserWidget* widget);
	void RemoveFromLayer(UBaseUserWidget* widget);

	void HideCommonWindowIfVisible(UBaseUserWidget* exceptWidget = nullptr);

	UFUNCTION(BlueprintCallable)
		void OnAndroidBack();

	UBaseUserWidget* GetMainWidget() { return MainWidget; }
private:
	UPROPERTY(Transient)
		UBaseUserWidget* MainWidget = nullptr;



	//
	// Load widget
public:
	UBaseUserWidget* CreateMainWidget(TSubclassOf<UBaseUserWidget> path);
	UBaseUserWidget* GetWidget(EWidgetType type, bool forceLoad = false);
private:
	UBaseUserWidget* CreateWidget(TSubclassOf<UBaseUserWidget> path);
	UBaseUserWidget* CreateWidget(EWidgetType type);

	UPROPERTY(Transient)
	TMap<EWidgetType, UBaseUserWidget*> LoadedWidgetContainer;



	//
	// Widget Visible
public:
	void SetHiddenWidget(UWidget* widget, bool hidden, ESlateVisibility showVisiblity = ESlateVisibility::SelfHitTestInvisible);
	void SetDimmedWidget(UWidget* widget, bool dimmed, ESlateVisibility showVisiblity = ESlateVisibility::SelfHitTestInvisible);

	bool IsHiddenWidget(UWidget* widget) const;
	bool IsDimmedWidget(UWidget* widget) const;
private:
	UPROPERTY()
		TMap<UWidget*, FWidgetVisibleInfo> WidgetVisibleInfoContainer;


	//
	// UI Layer
public:
	class UUILayer* GetUILayer();
private:
	UPROPERTY()
		class UUILayer* UILayer;
};

