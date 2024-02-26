// Copyright Epic Games, Inc. All Rights Reserved.
#include "BasicGameMode.h"
#include "../Common/MyGameInstance.h"
#include "BaseHUD.h"

ABasicGameMode::ABasicGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABasicGameMode::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* gameInstance = UMyGameInstance::Get();
	if (IsValid(gameInstance))
		gameInstance->InitGameMode(this);

	if (GetWorld()->GetFirstPlayerController())
		Hud = Cast<ABaseHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (Hud.IsValid())
	{
		Hud->InitializeHud();
		Hud->CreateMainWidget(MainWidget);
	}
}

void ABasicGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
