// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "System/CommonTypes.h"
#include "F_InventoryItem.generated.h"


class UInventoryComponent;



/**
 * @struct F_InventoryItem
 * Item struct used for storing inventory related item information.
 * 
 */
USTRUCT()
struct F_InventoryItem
{
    GENERATED_BODY()

public:
    /** Pointer to item's class */
    TSubclassOf<UBaseItem> ItemClass;

    /** Quantity of item */
    int32 Quantity;

    /** Inventory which the item belongs to */
    UInventoryComponent* OwningInventory;

    /** Location of the item in the inventory */
    int32 IndexLocation;

    /** Type of item */
    EItemType ItemType;

    /** Is multiple copies of the came object should be stacked */
    bool bShouldStack;

    // Default constructor and Destructor
    F_InventoryItem();
    ~F_InventoryItem();

    // Other constructors
    F_InventoryItem(const F_InventoryItem& Item);
    
};