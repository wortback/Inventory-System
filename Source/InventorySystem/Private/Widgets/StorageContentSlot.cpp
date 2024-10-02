// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StorageContentSlot.h"
#include "Components/TextBlock.h"
#include "Items/BaseItem.h"


void UStorageContentSlot::NativeConstruct()
{
	UBaseItem* BaseItem = Cast<UBaseItem>(SlotItem.ItemClass->GetDefaultObject(true));
	if (BaseItem)
	{
		// Formats the item name in the following way: "[EItemType] ItemName"
		FString Name = BaseItem->ItemName.ToString();
		SlotText->SetText(FText::FromString(("[") + EItemTypeToString(SlotItem.ItemType) + FString("] ") + Name));
	}
}
