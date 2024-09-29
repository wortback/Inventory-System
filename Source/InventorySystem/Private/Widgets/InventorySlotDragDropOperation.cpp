// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotDragDropOperation.h"
#include "Widgets/InventorySlot.h"

void UInventorySlotDragDropOperation::UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor)
{
	UnderDragSlot = SlotUnderCursor;
}
