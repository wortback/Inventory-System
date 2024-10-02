// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StorageContentWidget.h"
#include "Inventory/BaseStorage.h"
#include "Widgets/StorageContentSlot.h"
#include "Inventory/F_InventoryItem.h"
#include "Items/BaseItem.h"
#include "Items/BaseConsumable.h"
#include "System/CommonTypes.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"



void UStorageContentWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (OwningStorageClass && ContentSlotClass)
	{
		ABaseStorage* Storage = Cast<ABaseStorage>(OwningStorageClass->GetDefaultObject());
		if (Storage)
		{
			for (const F_InventoryItem& Item : Storage->GetStoredItems())
			{
				if (Item.ItemType != EItemType::EIT_None && SlotBox)
				{
					UStorageContentSlot* ChildSlot = CreateWidget<UStorageContentSlot>(GetWorld(), ContentSlotClass);
					ChildSlot->SlotItem = Item;

					SlotBox->AddChildToWrapBox(ChildSlot);
				}
			}
		}
		
	}
}


