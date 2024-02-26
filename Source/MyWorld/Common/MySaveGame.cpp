// Fill out your copyright notice in the Description page of Project Settings.
#include "MySaveGame.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

FString UMySaveGame::SaveSlotName = TEXT("NBSAVEGAME");
uint32 UMySaveGame::UserIndex = 0;

UEditorConfigData* UEditorConfigData::InstanceObj = nullptr;

UMySaveGame::UMySaveGame()
{
	
}

UMySaveGame* UMySaveGame::Get()
{
	return UMyGameInstance::Get()->GetSaveGame();
}

void UMySaveGame::Save()
{
	UGameplayStatics::SaveGameToSlot(this, UMySaveGame::SaveSlotName, UMySaveGame::UserIndex);
}

UEditorConfigData::~UEditorConfigData()
{
	InstanceObj = nullptr;
}

UEditorConfigData* UEditorConfigData::Get()
{
	if (!IsValid(InstanceObj))
	{
		InstanceObj = NewObject<UEditorConfigData>();
		InstanceObj->AddToRoot();
	}

	return InstanceObj;
}