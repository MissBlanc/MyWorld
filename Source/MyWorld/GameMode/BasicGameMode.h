// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasicGameMode.generated.h"

class ABaseHUD;
class UBaseUserWidget;

UCLASS(minimalapi)
class ABasicGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABasicGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;



	//
	// HUD
	//
public:
	ABaseHUD* GetHUD() const { return Hud.IsValid() ? Hud.Get() : nullptr; }

protected:
	TWeakObjectPtr<ABaseHUD> Hud = nullptr;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UBaseUserWidget> MainWidget;
};



