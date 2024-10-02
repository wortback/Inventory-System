// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlot.h"
#include "Widgets/PrimaryHUDWidget.h"
#include "Widgets/InventorySlotDragDropOperation.h"
#include "Items/BaseItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

// Logging
#include "InventorySystem.h"


void UInventorySlot::NativeConstruct()
{
	if (Item.Quantity > 0)
	{
		UBaseItem* BaseItem = Cast<UBaseItem>(Item.ItemClass->GetDefaultObject(true));
		
		if (BaseItem)
		{	

			if (BaseItem->Thumbnail) 
				Thumbnail->SetBrushFromTexture(BaseItem->Thumbnail);

			ItemName->SetText(BaseItem->ItemName);
			if (BaseItem->bIsStackable)
			{
				AmountText->SetText(FText::FromString(FString::FromInt(Item.Quantity)));
			}
		}
	}
	else
	{
		Thumbnail->SetColorAndOpacity(FLinearColor::Transparent);
		ItemName->SetText(FText::GetEmpty());
		AmountText->SetText(FText::GetEmpty());
	}
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (OwningHUD)
	{
		UE_LOG(LogInventoryHUD, Log, TEXT("ItemType %s"), *(EItemTypeToString(Item.ItemType)));
		UE_LOG(LogInventoryHUD, Log, TEXT("ItemQuantity %d"), Item.Quantity);
		IInventoryWidgetsInterface* Interface = Cast<IInventoryWidgetsInterface>(OwningHUD);
		if (Interface)
		{
			Interface->UpdateSlotUnderCursor(this);
		}
	}
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (OwningHUD)
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
