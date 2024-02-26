// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM()
enum class EWidgetType : uint8
{
	None,
	UILayer,
	BasicMainWidget,
	BasicTestWindow,
	BasicTestPopup1,
	BasicTestPopup2,
};

UENUM()
enum class EWidgetLayerType : uint8
{
	None,
	MainHud,
	MainMenu,
	Window,
	Popup,
	Sequence,
	System,

	Etc
};