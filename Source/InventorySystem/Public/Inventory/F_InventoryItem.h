// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "F_InventoryItem.generated.h"


class UInventoryComponent;


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


/**
 * @struct F_InventoryItem
 * Item struct used for storing inventory related item information.
 * 
 */
USTRUCT(BlueprintType)
struct F_InventoryItem
{
    GENERATED_BODY()

public:
    /** Pointer to item's class */
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TSubclassOf<UBaseItem> ItemClass;

    /** Quantity of item */
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    int32 Quantity;

    /** Inventory which the item belongs to */
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UInventoryComponent* OwningInventory;

    /** Location of the item in the inventory */
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    int32 IndexLocation;

    /** Type of item */
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    EItemType ItemType;

    // Default constructor and Destructor
    F_InventoryItem();
    ~F_InventoryItem();

    // Other constructors
    F_InventoryItem(const F_InventoryItem& Item);
    
};