// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

class UNBCharacterSortListItemData;
class UNBInventorySortListItemData;
class UNBCommonSortListItemData;
class FJsonObject;

 namespace MyDelegate
 {
	 DECLARE_DELEGATE(FOnNormalDelegate);
	 DECLARE_DELEGATE_OneParam(FOnInt32ParamDelegate, int32);
	 DECLARE_DELEGATE_OneParam(FOnInt64ParamDelegate, int64);
	 DECLARE_DELEGATE_OneParam(FOnFloatParamDelegate, float);
 	 DECLARE_DELEGATE_OneParam(FOnUint64ParamDelegate, uint64);
	 DECLARE_DELEGATE_OneParam(FOnFStringParamDelegate, FString);

	 DECLARE_MULTICAST_DELEGATE(FOnNormalMultiDelegate);

	 DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorParamMultiDelegate, AActor*);
	 DECLARE_MULTICAST_DELEGATE_OneParam(FOnInt32ParamMultiDelegate, int32);

	 DECLARE_DELEGATE_OneParam(FToggleDelegate, bool);

	 DECLARE_DELEGATE_OneParam(FLoadDelegate, TArray<UObject*>);

	 DECLARE_DELEGATE_OneParam(FOnClickItem, const UObject*);
	 DECLARE_DELEGATE_OneParam(FOnClickUObject, UObject*);

	 DECLARE_DELEGATE_OneParam(FOnFinishAnimation, UObject*);
 }