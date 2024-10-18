// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlotDragDropOperation.h"
#include "Widgets/InventorySlot.h"
#include "Widgets/PrimaryHUDWidget.h"

// Logging
#include "InventorySystem.h"



UInventorySlotDragDropOperation::UInventorySlotDragDropOperation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (UnderDragSlot)
	{
		UE_LOG(LogInventoryHUD, Warning, TEXT("SLOT"));
	}
}

void UInventorySlotDragDropOperation::UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor)
{
	UnderDragSlot = SlotUnderCursor;
}

void UInventorySlotDragDropOperation::Drop(const FPointerEvent& PointerEvent)
{
	UE_LOG(LogInventoryHUD, Warning, TEXT("Event Drop."));

	if (UnderDragSlot)
	{
		if (UnderDragSlot != Payload)
		{
			UInventorySlot* DraggedSlot = Cast<UInventorySlot>(Payload);
			if (DraggedSlot)
			{
				UnderDragSlot->OwningHUD->OnItemDrop(UnderDragSlot, DraggedSlot);
			}
		}
	}
}

void UInventorySlotDragDropOperation::DragCancelled(const FPointerEvent& PointerEvent)
{
	
}

void UInventorySlotDragDropOperation::Dragged(const FPointerEvent& PointerEvent)
{
	UE_LOG(LogInventoryHUD, Warning, TEXT("Event Dragged."));
}
