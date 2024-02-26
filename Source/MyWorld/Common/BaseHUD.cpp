// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseHUD.h"
#include "../UI/UILayer.h"
#include "WidgetTable.h"
#include "MyGameInstance.h"
#include "BasicGameMode.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

// #if ENABLE_DRAW_DEBUG
// 	ANBLocalPlayerCharacter* localPlayerCharacter = ANBLocalPlayerCharacter::Get();
// 	if (IsValid(localPlayerCharacter) && localPlayerCharacter->CheckSelectedPlayCharacter())
// 	{
// 		ANBPlayerController* playerController = ANBPlayerController::Get();
// 		if (IsValid(playerController) && IsValid(playerController->GetCheatManager()))
// 		{
// 			int32 viewportSizeX, viewportSizeY;
// 			playerController->GetViewportSize(viewportSizeX, viewportSizeY);
// 
// 			if (playerController->GetCheatManager()->CheckDebugOptimizeInfo())
// 			{
// 				FString debugString = "";
// 
// 				debugString += FString::Printf(TEXT("Character Count : %d.\n"), UNBSignificanceManager::CharacterCount);
// 				debugString += FString::Printf(TEXT("Active Character Count : %d.\n"), UNBSignificanceManager::ActiveCharacterCount);
// 				debugString += FString::Printf(TEXT("Loaded Character Count : %d.\n"), UNBSignificanceManager::LoadedCharacterCount);
// 
// 				debugString += FString::Printf(TEXT("Tick Character Count : %d.\n"), UNBSignificanceManager::TickCharacterCount);
// 				debugString += FString::Printf(TEXT("Render Character Count : %d.\n"), UNBSignificanceManager::RenderCharacterCount);
// 				debugString += FString::Printf(TEXT("AI Playing Character Count : %d.\n"), UNBSignificanceManager::AiPlayingCharacterCount);
// 				debugString += FString::Printf(TEXT("PathFollowing Character Count : %d.\n"), UNBSignificanceManager::PathFollowingCharacterCount);
// 				debugString += FString::Printf(TEXT("Async Path Find Count : %d.\n"), UNBSignificanceManager::AsyncPathFindCount);
// 
// 				debugString += FString::Printf(TEXT("Top Has Niagara Count : %d.\n"), UNBSignificanceManager::TopHasNiagaraCount);
// 
// 				debugString += FString::Printf(TEXT("Significance Distance : %d.\n"), UNBSignificanceManager::SignificanceDistance);
// 				debugString += FString::Printf(TEXT("Significance Character Count : %d.\n"), UNBSignificanceManager::SignificanceCharacterCount);
// 				debugString += FString::Printf(TEXT("Significance Cull Character Count : %d.\n"), UNBSignificanceManager::SignificanceCullCharacterCount);
// 
// 				debugString += "\nTick Character List\n";
// 				for (int32 i = 0, len = UNBSignificanceManager::TickCharacterList.Num(); i < len; ++i)
// 				{
// 					const TWeakObjectPtr<ANBCharacter>& tickCharacter = UNBSignificanceManager::TickCharacterList[i];
// 					if (!tickCharacter.IsValid())
// 						continue;
// 
// 					debugString += FString::Printf(TEXT("%s :     %s.\n"), *tickCharacter->GetName(), tickCharacter->GetCharacterAsset() ? *tickCharacter->GetCharacterAsset()->GetName() : TEXT(""));
// 				}
// 
// 				debugString += "\nRender Character List\n";
// 				for (int32 i = 0, len = UNBSignificanceManager::RenderCharacterList.Num(); i < len; ++i)
// 				{
// 					const TWeakObjectPtr<ANBCharacter>& renderCharacter = UNBSignificanceManager::RenderCharacterList[i];
// 					if (!renderCharacter.IsValid())
// 						continue;
// 
// 					debugString += FString::Printf(TEXT("%s :     %s.\n"), *renderCharacter->GetName(), renderCharacter->GetCharacterAsset() ? *renderCharacter->GetCharacterAsset()->GetName() : TEXT(""));
// 				}
// 
// 				DrawText(debugString, FColor::Yellow, 50.0f, viewportSizeY - 400.0f);
// 			}
// 
// 			if (playerController->GetCheatManager()->CheckDebugUILayer())
// 			{
// 				if (IsValid(UILayer))
// 				{
// 					FString debugString = "";
// 
// 					debugString += FString::Printf(TEXT("MainHud Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::MainHud));
// 					debugString += FString::Printf(TEXT("MainMenu Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::MainMenu));
// 					debugString += FString::Printf(TEXT("Window Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::Window));
// 					debugString += FString::Printf(TEXT("Popup Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::Popup));
// 					debugString += FString::Printf(TEXT("Sequence Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::Sequence));
// 					debugString += FString::Printf(TEXT("System Count : %d.\n"), UILayer->GetLayerWidgetNum(EWidgetLayerType::System));
// 
// 					DrawText(debugString, FColor::Yellow, 50.0f, viewportSizeY - 400.0f);
// 				}
// 			}
// 
// 			UNBSaveSystemData* saveSystem = UNBSaveSystemData::Get();
// 			if (IsValid(saveSystem))
// 			{
// 				if (saveSystem->AsyncLog)
// 				{
// 					UNBLoadManager* loadManager = UNBLoadManager::Get();
// 					if (IsValid(loadManager))
// 					{
// 						FString logString;
// 						loadManager->GetAsyncLog(logString);
// 						if (logString.IsEmpty() == false)
// 							DrawText(logString, FColor::Yellow, 50.0f, viewportSizeY - 300.0f);
// 					}
// 				}
// 			}
// 		}
// 	}
// #endif

// #if ENABLE_DRAW_DEBUG
// 	UNBSignificanceManager::TickCharacterCount = 0;
// 	UNBSignificanceManager::RenderCharacterCount = 0;
// 	UNBSignificanceManager::AiPlayingCharacterCount = 0;
// 	UNBSignificanceManager::PathFollowingCharacterCount = 0;
// 	UNBSignificanceManager::AsyncPathFindCount = 0;
// 	UNBSignificanceManager::TickCharacterList.Empty();
// 	UNBSignificanceManager::RenderCharacterList.Empty();
// #endif
}

void ABaseHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABaseHUD* ABaseHUD::Get()
{
// 	UNBGameInstance* gameInstance = UNBGameInstance::Get();
// 	if (!IsValid(gameInstance))
// 		return nullptr;
// 	ANBGameModeBase* gameMode = gameInstance->GetCurrentGameMode();
// 	if (!IsValid(gameMode))
// 		return nullptr;
// 
// 	ANBGameStateBase* gameState = gameMode->GetGameState<ANBGameStateBase>();
// 	if (!IsValid(gameState))
// 		return nullptr;
// 
// 	return gameState->GetHUD();
	UMyGameInstance* gameInstance = UMyGameInstance::Get();
	if (!IsValid(gameInstance))
		return nullptr;
	ABasicGameMode* gameMode = gameInstance->GetCurrentGameMode();
	if (!IsValid(gameMode))
		return nullptr;
	return gameMode->GetHUD();
}

ABaseHUD::ABaseHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}



void ABaseHUD::InitializeHud()
{

}

bool ABaseHUD::IsInLayer(UBaseUserWidget* widget) const
{
	if (!IsValid(widget))
		return false;
	if (!IsValid(UILayer))
		return false;

	return UILayer->IsInLayer(widget);
}

void ABaseHUD::AddToLayer(UBaseUserWidget* widget)
{
	if (!IsValid(widget))
		return;
	if (!IsValid(UILayer))
		return;

	UILayer->AddWidget(widget->GetWidgetLayerType(), widget);
}

void ABaseHUD::RemoveFromLayer(UBaseUserWidget* widget)
{
	if (!IsValid(widget))
		return;
	if (!IsValid(UILayer))
		return;

	UILayer->RemoveWidget(widget->GetWidgetLayerType(), widget);
}

void ABaseHUD::HideCommonWindowIfVisible(UBaseUserWidget* exceptWidget /*= nullptr*/)
{
	const UEnum* enumPtr = StaticEnum<EWidgetLayerType>();
	if (!enumPtr)
		return;

	const int32 len = enumPtr->NumEnums();
	for (int i = 0; i < len; ++i)
	{
		const EWidgetLayerType enumValue = (EWidgetLayerType)(enumPtr->GetValueByIndex(i));
		if (enumValue == EWidgetLayerType::MainHud)
			continue;

		FLayerInfo* layerInfo = UILayer->GetLayerInfo(enumValue);
		if (!layerInfo)
			continue;

		layerInfo->RemoveChildAll(exceptWidget);
	}
}

void ABaseHUD::OnAndroidBack()
{
	if (!IsValid(UILayer))
		return;

	if (!IsValid(UILayer->GetTopWidget()))
		return;

	UILayer->GetTopWidget()->OnClickBackButton();
}



//
// Load widget
UBaseUserWidget* ABaseHUD::CreateMainWidget(TSubclassOf<UBaseUserWidget> path)
{
	if (path == nullptr)
		return nullptr;

	if (!IsValid(GetUILayer()))
		return nullptr;

	MainWidget = CreateWidget(path);

	GetUILayer()->AddWidget(EWidgetLayerType::MainHud, MainWidget);

	return MainWidget;
}

UBaseUserWidget* ABaseHUD::CreateWidget(TSubclassOf<UBaseUserWidget> path)
{
	if (path == nullptr)
		return nullptr;

	return Cast<UBaseUserWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), path, NAME_None));
}

UBaseUserWidget* ABaseHUD::CreateWidget(EWidgetType type)
{
	UMyGameInstance* gameInstance = UMyGameInstance::Get();
	if (!IsValid(gameInstance))
		return nullptr;

	const FWidgetData* widgetData = gameInstance->GetWidgetTableData(type);
	if (!widgetData)
		return nullptr;

	UBaseUserWidget* widget = CreateWidget(widgetData->WidgetObject);
	if (!IsValid(widget))
		return nullptr;

	LoadedWidgetContainer.Emplace(type, widget);
	return widget;
}

UBaseUserWidget* ABaseHUD::GetWidget(EWidgetType type, bool forceLoad /*= false*/)
{
	if (!forceLoad)
	{
		UBaseUserWidget* findWidget = LoadedWidgetContainer.Contains(type) ? LoadedWidgetContainer[type] : nullptr;
		if (IsValid(findWidget))
		{
			return findWidget;
		}
	}

	return CreateWidget(type);
}


//
// Widget Visible
void ABaseHUD::SetHiddenWidget(UWidget* widget, bool hidden, ESlateVisibility showVisibilityType /*= ESlateVisibility::SelfHitTestInvisible*/)
{
	if (!IsValid(widget))
		return;

	if (!WidgetVisibleInfoContainer.Contains(widget))
	{
		FWidgetVisibleInfo widgetVisibleInfo;
		widgetVisibleInfo.ShowVisibilityType = showVisibilityType;
		WidgetVisibleInfoContainer.Emplace(widget, widgetVisibleInfo);
	}

	FWidgetVisibleInfo* widgetVisibleInfo = WidgetVisibleInfoContainer.Find(widget);
	if (!widgetVisibleInfo)
		return;

	const int32 addStack = hidden ? 1 : -1;
	const int32 resultStack = widgetVisibleInfo->HiddenStack + addStack;
	widgetVisibleInfo->HiddenStack = FMath::Max(0, resultStack);

	const ESlateVisibility visibility = IsHiddenWidget(widget) ? ESlateVisibility::Collapsed : widgetVisibleInfo->ShowVisibilityType;
	if (widget->GetVisibility() == visibility)
		return;

	widget->SetVisibility(visibility);
}

void ABaseHUD::SetDimmedWidget(UWidget* widget, bool dimmed, ESlateVisibility showVisibilityType /*= ESlateVisibility::SelfHitTestInvisible*/)
{
	if (!IsValid(widget))
		return;

	if (!WidgetVisibleInfoContainer.Contains(widget))
	{
		FWidgetVisibleInfo widgetVisibleInfo;
		widgetVisibleInfo.ShowVisibilityType = showVisibilityType;
		WidgetVisibleInfoContainer.Emplace(widget, widgetVisibleInfo);
	}

	FWidgetVisibleInfo* widgetVisibleInfo = WidgetVisibleInfoContainer.Find(widget);
	if (!widgetVisibleInfo)
		return;

	const int32 addStack = dimmed ? 1 : -1;
	const int32 resultStack = widgetVisibleInfo->DimmedStack + addStack;
	widgetVisibleInfo->DimmedStack = FMath::Max(0, resultStack);

	const ESlateVisibility visibility = IsDimmedWidget(widget) ? widgetVisibleInfo->ShowVisibilityType : ESlateVisibility::Collapsed;
	if (widget->GetVisibility() == visibility)
		return;

	widget->SetVisibility(visibility);
}

bool ABaseHUD::IsHiddenWidget(UWidget* widget) const
{
	if (!IsValid(widget))
		return false;

	if (!WidgetVisibleInfoContainer.Contains(widget))
		return false;

	const FWidgetVisibleInfo* widgetVisibleInfo = WidgetVisibleInfoContainer.Find(widget);
	if (!widgetVisibleInfo)
		return false;

	return widgetVisibleInfo->HiddenStack > 0;
}

bool ABaseHUD::IsDimmedWidget(UWidget* widget) const
{
	if (!IsValid(widget))
		return false;

	if (!WidgetVisibleInfoContainer.Contains(widget))
		return false;

	const FWidgetVisibleInfo* widgetVisibleInfo = WidgetVisibleInfoContainer.Find(widget);
	if (!widgetVisibleInfo)
		return false;

	return widgetVisibleInfo->DimmedStack > 0;
}

class UUILayer* ABaseHUD::GetUILayer()
{
	if (!IsValid(UILayer))
	{
		UILayer = Cast<UUILayer>(GetWidget(EWidgetType::UILayer));

		if (IsValid(UILayer))
			UILayer->InitLayerInfo();
	}
	return UILayer;
}
