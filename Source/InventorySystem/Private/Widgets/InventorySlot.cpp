// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlot.h"
#include "Widgets/PrimaryHUDWidget.h"
#include "Widgets/InventorySlotDragDropOperation.h"

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (OwningHUDClass && OwningHUD)
	{
		IInventoryWidgetsInterface* Interface = Cast<IInventoryWidgetsInterface>(OwningHUD);
		if (Interface)
		{
			Interface->UpdateSlotUnderCursor(this);
		}
	}
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (OwningHUDClass && OwningHUD)
	{
		IInventoryWidgetsInterface* Interface = Cast<IInventoryWidgetsInterface>(OwningHUD);
		if (Interface)
		{
			Interface->UpdateSlotUnderCursor(nullptr);
		}
	}
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FKey DragKey = FKey("RightMouseButton");
	if (InMouseEvent.GetEffectingButton() == DragKey || InMouseEvent.IsTouchEvent())
	{
		TSharedPtr<SWidget> SlateWidgetDetectingDrag = GetCachedWidget();
		if (SlateWidgetDetectingDrag.IsValid())
		{
			FReply Reply = FReply::Handled();
			return Reply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
		}
	}

	return FReply::Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, 
	UDragDropOperation*& OutOperation)
{
	UE_LOG(LogTemp, Warning, TEXT("Drag Inventory slot detected"));

	// if the slot is empty, don't drag anything
	if (!(Item.ItemClass == UBaseItem::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Drag possible."));
		UInventorySlotDragDropOperation* DragNDrop = NewObject<class UInventorySlotDragDropOperation>();
		DragNDrop->Payload = this;
		DragNDrop->DefaultDragVisual = this;

		OutOperation = DragNDrop;
	}
}
