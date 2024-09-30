// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/CommonTypes.h"
#include "InventoryWidget.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogInventoryHUD, Log, All)


class UWrapBox;
class UTextBlock;



/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UWrapBox> InventoryBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> TabName;

public:
	/**
	 * Function that returns the ItemType of the items located on the currently opened inventory tab.
	 * Since Weapons and Armour sets are displayed on the same tab, EIT_Armour is returned for both of them.
	 */
	EItemType GetItemTypeForCurrentTab();

private:
	/** Inventory Tab that is currently displayed */
	EInventoryWidgetTab CurrentTab = EInventoryWidgetTab::EIWT_Equipment;

public:
	FORCEINLINE EInventoryWidgetTab GetCurrentTab() const { return CurrentTab; }
	FORCEINLINE void SetCurrentTab(EInventoryWidgetTab Tab) { CurrentTab = Tab; }
};
