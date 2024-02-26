// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseUserWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "BaseUserWidget.h"
#include "BaseUserWidget.h"
#include "Components/AudioComponent.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CommonEnum.h"
#include "BaseHUD.h"

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CurrentVisiblity = GetVisibility();

	if (CurrentVisiblity != ESlateVisibility::Collapsed)
	{
		if (IsValid(Ani_Show) &&
			!IsAnimationPlaying(Ani_Show))
		{
			PlayAnimation(Ani_Show);
		}
	}
}

void UBaseUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	LastTickTime = GetWorld()->GetTimeSeconds();
}

UBaseUserWidget::UBaseUserWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//CurrentVisiblity = GetVisibility();
}

void UBaseUserWidget::AddWidgetToLayer()
{
	ABaseHUD* HUD = ABaseHUD::Get();
 	if (IsValid(HUD))
 		HUD->AddToLayer(this);
}

void UBaseUserWidget::RemoveWidgetFromLayer()
{
 	ABaseHUD* HUD = ABaseHUD::Get();
 	if (IsValid(HUD))
 		HUD->RemoveFromLayer(this);

	ForceLayerType = EWidgetLayerType::None;
}

void UBaseUserWidget::SetVisibility(ESlateVisibility InVisibility)
{
	if (InitVisibility && CurrentVisiblity == InVisibility)
		return;

	InitVisibility = true;
	CurrentVisiblity = InVisibility;

	if (InVisibility != ESlateVisibility::Collapsed)
	{
		if (IsValid(Ani_Show) &&
			!IsAnimationPlaying(Ani_Show))
		{
			PlayAnimation(Ani_Show);
		}
	}

	Super::SetVisibility(InVisibility);
}

void UBaseUserWidget::SetVisibilityForce(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);
}

void UBaseUserWidget::Refresh()
{
	Super::SetVisibility(CurrentVisiblity);
}

bool UBaseUserWidget::IsInViewportPosition() const
{
	if (UWorld* world = GetWorld())
	{
		const FGeometry& geometry = GetCachedGeometry();

		FVector2D pixelPosition;
		FVector2D widgetViewportPosition;
		USlateBlueprintLibrary::LocalToViewport(world, geometry, FVector2D(0), pixelPosition, widgetViewportPosition);

		FVector2D widgetViewportPositionWithScale = widgetViewportPosition * UWidgetLayoutLibrary::GetViewportScale(world);

		FVector2D viewportSize;
		world->GetGameViewport()->GetViewportSize(viewportSize);

		if (FMath::IsWithin<float, float>(widgetViewportPositionWithScale.X, 0.f, viewportSize.X) &&
			FMath::IsWithin<float, float>(widgetViewportPositionWithScale.Y, 0.f, viewportSize.Y))
			return true;
	}

	return false;
}

void UBaseUserWidget::ShowLayer()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UBaseUserWidget::HideLayer()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBaseUserWidget::Open()
{
// 	if (IsValid(UNBAudioManager::Get()))
// 	{
// 		UNBAudioManager::Get()->ApplyWidgetSoundInfo(this);
// 	}
}

void UBaseUserWidget::Close()
{
// 	if (IsValid(UNBAudioManager::Get()))
// 	{
// 		UNBAudioManager::Get()->RestoreWidgetSoundInfo(this);
// 	}
}

EWidgetLayerType UBaseUserWidget::GetWidgetLayerType() const
{
	return ForceLayerType != EWidgetLayerType::None ? ForceLayerType : WidgetLayerType;
}