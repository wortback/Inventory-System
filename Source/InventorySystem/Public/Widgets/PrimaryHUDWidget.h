// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/InventoryWidget.h"
#include "Interfaces/InventoryWidgetsInterface.h"
#include "Interfaces/InventoryHUDInterface.h"
#include "PrimaryHUDWidget.generated.h"



class UInventoryComponent;
class UInventorySlot;
class UPlayerInventoryWindow;
class UTransferItemsWidget;

//Minimum number of item instances stacked in a slot required to open the slider widget
constexpr int32 MIN_REQUIRED_FOR_SLIDER = 6;


/**
 * Widget class that displays the player's inventory and inventories in the trade mode.
 */
UCLASS()
class INVENTORYSYSTEM_API UPrimaryHUDWidget : public UUserWidget, public IInventoryWidgetsInterface
{
	GENERATED_BODY()

public:
	/** Inventory Menu */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventoryWidget> InventoryMenu;

	/** Item exchange with NPC (trade mode) */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPlayerInventoryWindow> PlayerInventory;

	/** Item exchange with NPC (trade mode) */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPlayerInventoryWindow> NPCInventory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Subwidget Classes")
	TSubclassOf<UInventorySlot> InventorySlotClass;

	/** The class of the widget used to set the desired amount of copies of an item to be transferred */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Subwidget Classes")
	TSubclassOf<UTransferItemsWidget> TransferItemsWidgetClass;

	/** The widget that sets the desired amount of copies of the selected item to be transferred */
	UTransferItemsWidget* TransferItemsWidget;

	/** The slot the mouse is currently hovering over */
	UInventorySlot* OverSlot;

public:
	void ShowPlayerInventory(bool bShowInventory);

	void ShowNPCInventory(bool bShowInventory);

	/** Update the inventory menu */
	void UpdateInventory(const UInventoryComponent* InventoryComponent);

	/** Update inventories in the trade mode */
	void UpdateInventory(const UInventoryComponent* PlayerComp, const UInventoryComponent* NPCComp);

	/**
	 * Updates OverSlot to the passed slot. 
	 */
	UFUNCTION()
	virtual void UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor) override;

	/** Update inventory menus */
	void UpdateHUD();

	void OnItemDrop(UInventorySlot* UnderDragSlot, UInventorySlot* DragSlot);

private:
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	/** Collapses all inventories (player's and inventories in the trade mode (i.e. the player's and npc's)) */
	void CloseInventory();

	void ExecuteKeyBinding(FName Key);

	void ExecuteEKey(IInventoryHUDInterface* Interface);

	void UpdateEquippedAndQASlots(TObjectPtr<UInventorySlot> InventorySlot, const F_InventoryItem* Item);

	/** For OnSliderValueConfirmed Event */
	UFUNCTION()
	void HandleSliderValueConfirmed(int32 SliderValue);

	/**
	 * Create widget that allows to specify the number of items to be transferred (TransferItemsWidget)
	 * 
	 * @param ItemSlot Slot that contains the item that will be transferred
	 */
	void CreateTransferWidget(UInventorySlot* ItemSlot);
};
