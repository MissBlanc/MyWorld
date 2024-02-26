// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWindow.h"
#include "ActorWindow.generated.h"

/**
 * 
 */
UCLASS()
class MYWORLD_API UActorWindow : public UBaseWindow
{
	GENERATED_BODY()
public:
	virtual void Open() override;
	virtual void Close() override;

	virtual void ShowLayer() override;
	virtual void HideLayer() override;

	//
	// UI Actor
protected:
	virtual void InitUICharacterActor(bool isShow);
	virtual void RefreshUICharacterActor();

// 	UPROPERTY(Transient)
// 		class AUIPlaceActor* UIPlaceActor;

	//
	// Cache View Target
protected:
	TWeakObjectPtr< AActor> CacheViewTarget = nullptr;
};



