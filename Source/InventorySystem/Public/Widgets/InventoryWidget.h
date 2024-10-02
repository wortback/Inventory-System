// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/CommonTypes.h"
#include "InventoryWidget.generated.h"





class UWrapBox;
class UTextBlock;
class UTabButtonWidget;


/**
 * Widget that displays the content of InventoryComponent, namely contains the corresponding slots of 4 items arrays.
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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTabButtonWidget> TabSwitch;

public:
	/**
	 * Function that returns the ItemType of the items located on the currently opened inventory tab.
	 * Since Weapons and Armour sets are displayed on the same tab, EIT_Armour is returned for both of them.
	 */
	EItemType GetItemTypeForCurrentTab();

	void UpdateMenu();

	virtual void NativeConstruct() override;

public:
	EInventoryWidgetTab GetCurrentTab() const;
	void SetCurrentTab(EInventoryWidgetTab Tab);
};
