// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/CommonTypes.h"
#include "InventoryWidget.generated.h"





class UWrapBox;
class UTextBlock;
class UTabButtonWidget;
class UInventorySlot;
class UPlayerInventoryWindow;


/**
 * Widget for the main inventory window
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPlayerInventoryWindow> PlayerInventoryWindow;

	// All these slots are referred as special slots
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> EquippedArmour;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> EquippedWeapon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> QuickSlot1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> QuickSlot2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> QuickSlot3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> QuickSlot4;



public:
	/** Update PlayerInventoryWindow */
	void UpdateMenu();

	/** Returns true if the DraggedSlot item can be dropped */
	bool CanDropOnSpecialSlot(UInventorySlot* UnderDragSlot, UInventorySlot* DraggedSlot);
};
