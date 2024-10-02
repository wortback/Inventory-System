// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/F_InventoryItem.h"


#define DEFAULT_INDEX_LOCATION -1



F_InventoryItem::F_InventoryItem()
{
    ItemClass = UBaseItem::StaticClass();
    Quantity = 0;
    IndexLocation = DEFAULT_INDEX_LOCATION;
    OwningInventory = nullptr;
    ItemType = EItemType::EIT_None;
}

F_InventoryItem::~F_InventoryItem()
{
}

F_InventoryItem::F_InventoryItem(const F_InventoryItem& Item)
{
    ItemClass = Item.ItemClass;
    Quantity = Item.Quantity;
    IndexLocation = Item.IndexLocation;
    OwningInventory = Item.OwningInventory;
    ItemType = Item.ItemType;
}
