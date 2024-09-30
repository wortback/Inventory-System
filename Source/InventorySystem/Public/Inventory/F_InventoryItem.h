// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "System/CommonTypes.h"
#include "F_InventoryItem.generated.h"


class UInventoryComponent;


/*
UENUM()
enum class EItemType : uint8
{
	EIT_Armour,
    EIT_Weapon,
	EIT_Quest,
	EIT_Consumable,
    EIT_Miscellaneous,
    EIT_None
};
*/

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

    FString ItemTypeToString();

    // Default constructor and Destructor
    F_InventoryItem();
    ~F_InventoryItem();

    // Other constructors
    F_InventoryItem(const F_InventoryItem& Item);
    
};