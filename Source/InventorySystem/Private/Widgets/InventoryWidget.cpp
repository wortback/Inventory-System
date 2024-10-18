// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/TabButtonWidget.h"
#include "Widgets/PlayerInventoryWindow.h"
#include "System/Defines.h"
#include "Widgets/InventorySlot.h"

//Logging
#include "InventorySystem.h"



void UInventoryWidget::UpdateMenu()
{
	PlayerInventoryWindow->UpdateMenu();
}



bool UInventoryWidget::CanDropOnSpecialSlot(UInventorySlot* UnderDragSlot, UInventorySlot* DraggedSlot)
{
	if (UnderDragSlot->Item.IndexLocation == EQ_ARMOUR_INDEX_LOCATION && DraggedSlot->Item.ItemType == EItemType::EIT_Armour)
	{
		return true;
	}
	else if (UnderDragSlot->Item.IndexLocation == EQ_WEAPON_INDEX_LOCATION && DraggedSlot->Item.ItemType == EItemType::EIT_Weapon)
	{
		return true;
	}
	else if (IsQAItemIndex(UnderDragSlot->Item.IndexLocation) && DraggedSlot->Item.ItemType == EItemType::EIT_Consumable)
	{
		return true;
	}
	return false;
}
