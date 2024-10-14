// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/InventoryWidget.h"
#include "Interfaces/InventoryWidgetsInterface.h"
#include "PrimaryHUDWidget.generated.h"



class UInventoryComponent;
class UInventorySlot;
class UPlayerInventoryWindow;
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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Subwidgets")
	TSubclassOf<UInventorySlot> InventorySlotClass;

	/** The slot the mouse is currently hovering over */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
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

private:
	/** Collapses all inventories (player's and inventories in the trade mode (i.e. the player's and npc's)) */
	void CloseInventory();

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void ExecuteKeyBinding(FName Key);

	void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
};
