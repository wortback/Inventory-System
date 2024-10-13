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
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UPrimaryHUDWidget : public UUserWidget, public IInventoryWidgetsInterface
{
	GENERATED_BODY()

public:
	/** Inventory Menu */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventoryWidget> InventoryMenu;

	/** Item exchange with NPC */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPlayerInventoryWindow> PlayerInventory;

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

	void UpdateInventory(const UInventoryComponent* InventoryComponent);

	void UpdateInventory(const UInventoryComponent* PlayerComp, const UInventoryComponent* NPCComp);

	void ClosePlayerInventory();

	void CloseNPCInventory();

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;

	/**
	 * Updates OverSlot to the passed slot. 
	 */
	UFUNCTION()
	virtual void UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor) override;
};
