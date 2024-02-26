// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"
#include "WidgetTable.h"
#include "MySaveGame.h"
#include "BasicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LevelTable.h"

UMyGameInstance* UMyGameInstance::InstanceObj = nullptr;
bool UMyGameInstance::DrawDebug = false;
bool UMyGameInstance::HideAllUI = false;
bool UMyGameInstance::DebugQuest = false;
bool UMyGameInstance::DebugDamage = false;
bool UMyGameInstance::DebugTableLog = false;
bool UMyGameInstance::DebugCamera = false;
bool UMyGameInstance::DebugFootstep = false;

UMyGameInstance* UMyGameInstance::UMyGameInstance::Get()
{
	if (GWorld && IsValid(InstanceObj) == false)
	{
		InstanceObj = GWorld->GetGameInstance<UMyGameInstance>();
}

	return InstanceObj;
}

bool UMyGameInstance::IsGameWorld()
{
#if WITH_EDITOR
	return GWorld != nullptr && GWorld->IsGameWorld();
#else
	return true;
#endif
}

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}



void UMyGameInstance::Init()
{
	Super::Init();

#if WITH_EDITOR
	DebugTableLog = true;
#endif

	if (FCoreUObjectDelegates::PostLoadMapWithWorld.IsBoundToObject(this) == false)
		PostLoadMapWithWorldHandle = FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UMyGameInstance::HandlePostLoadMapWithWorld);

// 	if (FCoreUObjectDelegates::PreLoadMap.IsBoundToObject(this) == false)
// 		FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::HandlePreLoadMap);

	if (!EnterBackgroundHandle.IsValid())
	{
		EnterBackgroundHandle = FCoreDelegates::ApplicationWillEnterBackgroundDelegate.AddUObject(this, &UMyGameInstance::HandleApplicationWillEnterBackground);
	}

	InitSaveGame();
	InitDataTable();
}

void UMyGameInstance::Shutdown()
{
	if (IsValid(SaveGame))
		SaveGame->Save();

	//UNBTableData::Get()->Reset();

	if (TickDelegateHandle.IsValid())
		TickDelegateHandle.Reset();

	EnterBackgroundHandle.Reset();
	PostLoadMapWithWorldHandle.Reset();

	InstanceObj = nullptr;

	Super::Shutdown();
}

void UMyGameInstance::FinishDestroy()
{
	EnterBackgroundHandle.Reset();
	PostLoadMapWithWorldHandle.Reset();

	InstanceObj = nullptr;

	Super::FinishDestroy();
}

void UMyGameInstance::InitGameMode(ABasicGameMode* gameMode)
{
	CurrentGameMode = gameMode;
}

void UMyGameInstance::InitSaveGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(UMySaveGame::SaveSlotName, UMySaveGame::UserIndex))
	{
		SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	}
	else
	{
		SaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(UMySaveGame::SaveSlotName, UMySaveGame::UserIndex));
	}
}

bool UMyGameInstance::DeleteSaveGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(UMySaveGame::SaveSlotName, UMySaveGame::UserIndex))
		return false;

	if (!UGameplayStatics::DeleteGameInSlot(UMySaveGame::SaveSlotName, UMySaveGame::UserIndex))
		return false;

	InitSaveGame();

	return true;
}



//
// Handle
//
void UMyGameInstance::HandleApplicationWillEnterBackground()
{
	// Update game data and save data.
}

void UMyGameInstance::HandlePostLoadMapWithWorld(UWorld* world)
{
	// Initialize Pool

	// Hud > MainWidget > Notify Map Name 처리
}



//
// Time Dilation
//
int64 UMyGameInstance::SetTimeDilationValue(float timeDilationValue)
{
	int64 handle = GenerateTimeDilationHandle();
	TimeDilationContainer.Emplace(handle, timeDilationValue);

	RefreshWorldTimeDilation();
	return handle;
}

void UMyGameInstance::RestoreTimeDilationValue(int64 handle)
{
	if (!TimeDilationContainer.Contains(handle))
		return;

	TimeDilationContainer.Remove(handle);

	RefreshWorldTimeDilation();
}

void UMyGameInstance::RefreshWorldTimeDilation()
{
	AWorldSettings* worldSettings = GetWorld()->GetWorldSettings();
	if (!IsValid(worldSettings))
		return;

	float calcValue = 1.f;
	for (auto iter = TimeDilationContainer.CreateIterator(); iter; ++iter)
	{
		calcValue *= iter.Value();
	}

	worldSettings->SetTimeDilation(calcValue);
}

int64 UMyGameInstance::GenerateTimeDilationHandle()
{
	if (TimeDilationHandle == TNumericLimits<int64>::Max())
		TimeDilationHandle = 0;

	return ++TimeDilationHandle;
}


//
// Widget Table
//
const FWidgetData* UMyGameInstance::GetWidgetTableData(EWidgetType widgetType) const
{
	if (!IsValid(WidgetTable))
		return nullptr;
	if (!WidgetTable->Data.Contains(widgetType))
		return nullptr;

	return &WidgetTable->Data[widgetType];
}

void UMyGameInstance::InitDataTable()
{
// 	const FSoftObjectPath widgetDataAssetPath = FString("/Content/Data/WidgetTable_BP.WidgetTable_BP");
// 	UObject* loadedObject = widgetDataAssetPath.TryLoad();
// 	WidgetTable = Cast<UWidgetTable>(loadedObject/*widgetDataAssetPath.TryLoad()*/);
// 
// 	const FSoftObjectPath levelDataAssetPath = FString("/Game/Data/LevelTable_BP.LevelTable_BP");
// 	loadedObject = levelDataAssetPath.TryLoad();
// 	LevelTable = Cast<ULevelTable>(loadedObject);
}

//
// Level
//
bool UMyGameInstance::GotoLevel(int32 levelId)
{
	if (!IsValid(LevelTable))
		return false;
	if (!LevelTable->Data.Contains(levelId))
		return false;

	UGameplayStatics::OpenLevel(GetWorld(), *LevelTable->Data[levelId]);
	return true;
}

