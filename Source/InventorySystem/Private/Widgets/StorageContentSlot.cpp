// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StorageContentSlot.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/TextBlock.h"
#include "Items/BaseItem.h"
#include "Components/Button.h"
#include "Interfaces/InventoryHUDInterface.h"

// Logging
#include "InventorySystem.h"


void UStorageContentSlot::NativeConstruct()
{
	UseButton->OnPressed.AddDynamic(this, &UStorageContentSlot::OnButtonClicked);

	UBaseItem* BaseItem = Cast<UBaseItem>(SlotItem->ItemClass->GetDefaultObject(true));
	if (BaseItem)
	{
		// Formats the item name in the following way: "[EItemType] ItemName"
		FString Name = BaseItem->ItemName.ToString();
		SlotText->SetText(FText::FromString(("[") + EItemTypeToString(SlotItem->ItemType) + FString("] ") + Name));
	}
}

void UStorageContentSlot::OnButtonClicked()
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		IInventoryHUDInterface* Interface = Cast<IInventoryHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			if (Interface->ProcessItem(SlotItem))
			{
				SlotItem->ClearItem();
				UE_LOG(LogInventoryHUD, Log, TEXT("Successfully collected the item from the storage."));
				
				RemoveFromParent();
			}	
		}
	}
}
