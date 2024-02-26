// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

UCLASS()
class MYWORLD_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static FString SaveSlotName;
	static uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Account)
		int64 PlayerID;

	UPROPERTY(VisibleAnywhere, Category = Account)
		int64 Gold;
	UPROPERTY(VisibleAnywhere, Category = Account)
		int64 FreeCash;
	UPROPERTY(VisibleAnywhere, Category = Account)
		int64 PaidCash;

	UPROPERTY(VisibleAnywhere, Category = Character)
		FVector LastLoc;
	UPROPERTY(VisibleAnywhere, Category = Character)
		FRotator LastRot;

	UPROPERTY(VisibleAnywhere, Category = Quest)
		TArray<int32> PlayQuestIdList;
	UPROPERTY(VisibleAnywhere, Category = Quest)
		TArray<int32> CanReceiveQuestList;
	UPROPERTY(VisibleAnywhere, Category = Quest)
		TArray<int32> WaitQuestList;
	UPROPERTY(VisibleAnywhere, Category = Quest)
		TArray<int32> CompleteQuestList;
	UPROPERTY(VisibleAnywhere, Category = Quest)
		int32 ChaseQuestId;

	UMySaveGame();

	static UMySaveGame* Get();
	void Save();
};

UCLASS(Config = Editor)
class MYWORLD_API UEditorConfigData : public UObject
{
	GENERATED_BODY()

public:
	~UEditorConfigData();

public:
	static UEditorConfigData* Get();

public:
	bool GetTestConfigBool() { return TestConfigBool; }

private:
	UPROPERTY(Config)
		bool TestConfigBool;
private:
	static UEditorConfigData* InstanceObj;
};