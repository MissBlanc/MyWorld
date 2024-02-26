// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWindow.h"
//#include "HUD.h"
//#include "DragInputWidget.h"
//#include "UIPlaceActor.h"
//#include "UIBaseActor.h"
//#include "LocalPlayerCharacter.h"
#include "UILayer.h"

#include <Kismet/GameplayStatics.h>
//#include "TimeOfDay.h"

void UActorWindow::Open()
{
	Super::Open();

// 	if (IsValid(BP_DragInput))
// 	{
// 		BP_DragInput->GetDragDelegate()->BindUObject(this, &UActorWindow::OnUpdateDragInput);
// 		BP_DragInput->GetDragPinchDelegate()->BindUObject(this, &UActorWindow::OnUpdatePinchInput);
// 
// #if WITH_EDITOR || PLATFORM_WINDOWS
// 		if(!InputComponent)
// 			InitializeInputComponent();
// 	
// 		InputComponent->BindAxis("MouseWheel", this, &UActorWindow::OnMouseWheel);
// #endif
// 	}
}

void UActorWindow::Close()
{
	Super::Close();

// 	if (IsValid(BP_DragInput))
// 	{
// 		BP_DragInput->GetDragDelegate()->Uind();
// 		BP_DragInput->GetDragPinchDelegate()->Uind();
// 
// #if WITH_EDITOR || PLATFORM_WINDOWS
// 		if(!InputComponent)
// 			InitializeInputComponent();
// 	
// 		InputComponent->RemoveAxisBinding("MouseWheel");
// #endif
// 	}
}


void UActorWindow::ShowLayer()
{
	Super::ShowLayer();

	InitUICharacterActor(true);
}

void UActorWindow::HideLayer()
{
	Super::HideLayer();

	InitUICharacterActor(false);
}





//
// UI Actor
void UActorWindow::InitUICharacterActor(bool isShow)
{
// 	if (!IsValid(UIPlaceActor))
// 		return;
// 
// 	UIPlaceActor->SetActorHiddenInGame(!isShow);
// 	UIPlaceActor->SetUIState(isShow);
// 
// 	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
// 	if (!IsValid(playerController))
// 		return;
// 
// 	ALocalPlayerCharacter* localPlayerCharacter = ALocalPlayerCharacter::Get();
// 	if (!IsValid(localPlayerCharacter))
// 		return;
// 
// 	if (isShow)
// 	{
// 		localPlayerCharacter->EnableWorldPartitionStreamingSourceComponent();
// 
// 		RefreshUICharacterActor();
// 
// 		CacheViewTarget = playerController->GetViewTarget();
// 
// 		playerController->SetViewTarget(UIPlaceActor);
// 	}
// 	else
// 	{
// 		localPlayerCharacter->DisableWorldPartitionStreamingSourceComponent();
// 
// 		if (CacheViewTarget.IsValid())
// 		{
// 			playerController->SetViewTarget(CacheViewTarget.Get());
// 			CacheViewTarget = nullptr;
// 		}
// 		else
// 		{
// 			localPlayerCharacter->SetViewTarget();
// 		}
// 	}
}

void UActorWindow::RefreshUICharacterActor()
{
// 	if(IsValid(UIPlaceActor) == false)
// 		return;
// 		
// 	UIPlaceActor->ProcessCameraMove(true);
}