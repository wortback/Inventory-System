// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventorySlot.h"
#include "Widgets/PrimaryHUDWidget.h"
#include "Widgets/InventorySlotDragDropOperation.h"
#include "Items/BaseItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Interfaces/InventoryWidgetsInterface.h"
#include "Kismet/GameplayStatics.h"

// Logging
#include "InventorySystem.h"


void UInventorySlot::UpdateSlotContent()
{
	if (Item.ItemType != EItemType::EIT_None)
	{
		UBaseItem* BaseItem = Cast<UBaseItem>(Item.ItemClass->GetDefaultObject(true));
		if (BaseItem)
		{
			SetBackgroundByItemRarity(BaseItem->ItemRarity);

			// Since by default the slot image is transparent, we set another colour to remove transparency of the image first
			Icon->SetColorAndOpacity(FLinearColor::White);
			Icon->SetBrushFromTexture(BaseItem->Thumbnail);

			if (BaseItem->bIsStackable)
			{
				AmountText->SetText(FText::FromString(FString::FromInt(Item.Quantity)));
			}
		}
	}
	else
	{
		Background->SetBrushFromTexture(EmptyBG);
		Icon->SetColorAndOpacity(FLinearColor::Transparent);
		AmountText->SetText(FText::GetEmpty());
	}
}

void UInventorySlot::NativeConstruct()
{
	if (Item.Quantity > 0)
	{
		UBaseItem* BaseItem = Cast<UBaseItem>(Item.ItemClass->GetDefaultObject(true));
		if (BaseItem)
		{	
			SetBackgroundByItemRarity(BaseItem->ItemRarity);
			if (BaseItem->Thumbnail)
			{
				Icon->SetColorAndOpacity(FLinearColor::White);
				Icon->SetBrushFromTexture(BaseItem->Thumbnail);
			}

			if (BaseItem->bIsStackable)
			{
				AmountText->SetText(FText::FromString(FString::FromInt(Item.Quantity)));
			}
		}
	}
	else
	{
		// NB: if SetBrushFromTexture is called, the image appears transparent, because the alpha 
		// set by transparent colour persists until modified
		Background->SetBrushFromTexture(EmptyBG);
		Icon->SetColorAndOpacity(FLinearColor::Transparent);
		AmountText->SetText(FText::GetEmpty());
	}
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (OwningHUD)
	{
		UE_LOG(LogInventoryHUD, Log, TEXT("ItemType %s"), *(EItemTypeToString(Item.ItemType)));
		UE_LOG(LogInventoryHUD, Log, TEXT("ItemQuantity %d"), Item.Quantity);
		UE_LOG(LogInventoryHUD, Log, TEXT("ItemIndexLocation %d"), Item.IndexLocation);
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
	UE_LOG(LogInventoryHUD, Warning, TEXT("Drag Inventory slot detected"));

	// if the slot is empty, don't drag anything
	if (!(Item.ItemClass == UBaseItem::StaticClass()))
	{
		UE_LOG(LogInventoryHUD, Log, TEXT("Drag possible."));
		UInventorySlotDragDropOperation* DragNDrop = NewObject<class UInventorySlotDragDropOperation>();
		DragNDrop->Payload = this;
		DragNDrop->DefaultDragVisual = this;
		DragNDrop->Dragged(InMouseEvent);

		OutOperation = DragNDrop;
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UE_LOG(LogInventoryHUD, Warning, TEXT("NativeOnDrop by slot %d"), this->Item.IndexLocation);
	UInventorySlotDragDropOperation* DragNDrop = Cast<UInventorySlotDragDropOperation>(InOperation);
	if (DragNDrop)
	{
		DragNDrop->Drop(InDragDropEvent);
	}

	if (OwningHUD)
	{
		OwningHUD->UpdateHUD();
	}
	

	return true;
}

void UInventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	IInventoryWidgetsInterface* Interface = Cast<IInventoryWidgetsInterface>(InOperation);
	if (Interface)
	{
		Interface->UpdateSlotUnderCursor(this);
	}
}

void UInventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	IInventoryWidgetsInterface* Interface = Cast<IInventoryWidgetsInterface>(InOperation);
	if (Interface)
	{
		Interface->UpdateSlotUnderCursor(nullptr);
	}
}

void UInventorySlot::SetBackgroundByItemRarity(EItemRarity ItemRarity)
{
	switch (ItemRarity)
	{
	case EItemRarity::EIR_Common:
		Background->SetColorAndOpacity(FLinearColor::White);
		Background->SetBrushFromTexture(CommonBG);
		break;
	case EItemRarity::EIR_Uncommon:
		Background->SetColorAndOpacity(FLinearColor::White);
		Background->SetBrushFromTexture(UncommonBG);
		break;
	case EItemRarity::EIR_Rare:
		Background->SetColorAndOpacity(FLinearColor::White);
		Background->SetBrushFromTexture(RareBG);
		break;
	case EItemRarity::EIR_Divine:
		Background->SetColorAndOpacity(FLinearColor::White);
		Background->SetBrushFromTexture(DivineBG);
		break;
	case EItemRarity::EIR_Cursed:
		Background->SetColorAndOpacity(FLinearColor::White);
		Background->SetBrushFromTexture(CursedBG);
		break;
	default:
		break;
	}
}
