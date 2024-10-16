// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/TabButtonWidget.h"
#include "Widgets/PlayerInventoryWindow.h"
#include "System/Defines.h"

//Logging
#include "InventorySystem.h"



void UInventoryWidget::UpdateMenu()
{
	PlayerInventoryWindow->UpdateMenu();
}

bool UInventoryWidget::IsSpecialSlotIndex(int32 Index)
{
	switch (Index)
	{
	case EQ_ARMOUR_INDEX_LOCATION:
	case EQ_WEAPON_INDEX_LOCATION:
	case QUICK_SLOT_1_INDEX_LOCATION:
	case QUICK_SLOT_2_INDEX_LOCATION:
	case QUICK_SLOT_3_INDEX_LOCATION:
	case QUICK_SLOT_4_INDEX_LOCATION:
		return true;
	default:
		return false;
	}
}
