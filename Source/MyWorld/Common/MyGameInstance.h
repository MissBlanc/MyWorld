// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

class ABasicGameMode;
class UMySaveGame;
class UWidgetTable;

struct FWidgetData;

enum class EWidgetType : uint8;

UCLASS()
class MYWORLD_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	static UMyGameInstance* Get();
	static bool IsGameWorld();

	UMyGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void FinishDestroy() override;

public:
	void InitGameMode(ABasicGameMode* gameMode);
	void InitSaveGame();
	bool DeleteSaveGame();

	ABasicGameMode* GetCurrentGameMode() const { return CurrentGameMode.IsValid() ? CurrentGameMode.Get() : nullptr; }



private:
	static UMyGameInstance* InstanceObj;

private:
	TWeakObjectPtr<ABasicGameMode> CurrentGameMode;

	FTSTicker::FDelegateHandle TickDelegateHandle;

public:
	static bool DebugDamage;
	static bool DebugQuest;
	static bool DrawDebug;
	static bool DebugTableLog;
	static bool DebugCamera;
	static bool DebugFootstep;

	static bool HideAllUI;

	bool IsSaveGame = true;

public:
// 	UPROPERTY(EditAnywhere)
// 		TSubclassOf<ANBLocalPlayerCharacter> LocalPlayCharacterClass;
// 
// 	UPROPERTY(EditAnywhere)
// 		TSubclassOf<ANBNpcCharacter> NpcCharacterClass;



	//
	// AsyncLoad
	//

public:
	UPROPERTY(EditAnywhere, Category = LEVEL)
	int32 MaxCharacterTemporaryLoadCount = 0;



	//
	// SaveGame
	//
public:
	UMySaveGame* GetSaveGame() { return SaveGame; }

private:
	UPROPERTY(Transient)
	UMySaveGame* SaveGame = nullptr;



	//
	// Handle
	//
private:
	void HandleApplicationWillEnterBackground();
	void HandlePostLoadMapWithWorld(UWorld* world);

	FDelegateHandle EnterBackgroundHandle;
	FDelegateHandle PostLoadMapWithWorldHandle;



	//
	// Time Dilation
	//
public:
	int64 SetTimeDilationValue(float timeDilationValue);
	void RestoreTimeDilationValue(int64 handle);
private:
	void RefreshWorldTimeDilation();
	int64 GenerateTimeDilationHandle();
	TMap<int64/*handle*/, float/*Time Dilation Value*/> TimeDilationContainer;
	int64 TimeDilationHandle;



	//
	// Widget Table
	//
public:
	const FWidgetData* GetWidgetTableData(EWidgetType widgetType) const;
private:
	void InitDataTable();

// 	UPROPERTY(EditAnywhere)
// 	TSubclassOf<class UWidgetTable> WidgetTableAsset;
// 	UPROPERTY(Transient)
// 	TSubclassOf<class ULevelTable> LevelTableAsset;
// 
// 	UPROPERTY(Transient)
// 	class UWidgetTable* WidgetTable;
// 	UPROPERTY(Transient)
// 	class ULevelTable* LevelTable;

 	UPROPERTY(EditAnywhere)
 	TObjectPtr<class UWidgetTable> WidgetTable;
 	UPROPERTY(EditAnywhere)
	TObjectPtr<class ULevelTable> LevelTable;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPrimaryDataAsset> TestTable;

	//
	// Level
	//
public:
	bool GotoLevel(int32 levelId);

};
