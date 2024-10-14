// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Interfaces/InventoryHUDInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "System/CommonTypes.h"
#include "System/Defines.h"

// Logging
#include "InventorySystem.h"





UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::ProcessItem(F_InventoryItem* Item, int32 Quantity /* = 1*/)
{
	if (Item->ItemType != EItemType::EIT_None)
	{
		int32 ItemIndexLocation = FindAvailableLocation(Item);
		UE_LOG(LogInventoryComponent, Log, TEXT("ItemType: %s"), *(EItemTypeToString(Item->ItemType)));

		if (ItemIndexLocation >= 0)
		{
			F_InventoryItem* AddedItem = AddItem(Item, ItemIndexLocation, Quantity);
			if (AddedItem->Quantity > 0)
			{
				ProcessItem(AddedItem, AddedItem->Quantity);
			}
			else
			{
				delete AddedItem;
				return true;
			}
		}
		else
		{
			UE_LOG(LogInventoryComponent, Warning, TEXT("Inventory is full"));
			return false;
		}
	}

	return false;
}

F_InventoryItem* UInventoryComponent::AddItem(F_InventoryItem* Item, int IndexLocation, int32 Quantity /*= 1*/)
{
	UE_LOG(LogInventoryComponent, Log, TEXT("Adding a new item of type %s"), *(EItemTypeToString(Item->ItemType)));

	F_InventoryItem* ItemAtLocation = &SetItemsForItemType(Item->ItemType)[IndexLocation];


	UBaseItem* DefaultItem = Cast<UBaseItem>(UBaseItem::StaticClass()->GetDefaultObject(true));
	
	int32 NewQuantity = ItemAtLocation->Quantity + Quantity;
	int32 QuantityClamped = FMath::Clamp(NewQuantity, 0, DefaultItem->StackSize);
	int32 DeltaQuantity = NewQuantity - FMath::Clamp(NewQuantity, 0, DefaultItem->StackSize);

	// Update member variables on the item st this particular slot
	ItemAtLocation->Quantity = QuantityClamped;
	ItemAtLocation->ItemClass = Item->ItemClass;
	ItemAtLocation->OwningInventory = this;
	ItemAtLocation->IndexLocation = IndexLocation;
	ItemAtLocation->ItemType = Item->ItemType;

	// A new F_InventoryItem Object that stores DeltaQuantity
	// if it is bigger than 0, will attempt to store the remaining copies of the item in a separate slot
	F_InventoryItem* Result = new F_InventoryItem(*Item);
	Result->Quantity = DeltaQuantity;

	return Result;
}

bool UInventoryComponent::RemoveItem(F_InventoryItem* Item, int32 Quantity)
{
	if (Item->ItemType != EItemType::EIT_None)
	{
		F_InventoryItem* ItemAtLocation = &SetItemsForItemType(Item->ItemType)[Item->IndexLocation];
		if (ItemAtLocation->Quantity == 1)
		{
			ItemAtLocation->ItemClass = UBaseItem::StaticClass();
			ItemAtLocation->OwningInventory = nullptr;
			ItemAtLocation->Quantity = 0;
			ItemAtLocation->ItemType = EItemType::EIT_None;
		}
		else if (ItemAtLocation->Quantity > Quantity)
		{
			ItemAtLocation->Quantity -= Quantity;
		}
		else
		{
			UE_LOG(LogInventoryComponent, Error, TEXT("Attempting to remove more item instances than are present. Aborting the operation."));
		}

		return true;
	}
	return false;
}

bool UInventoryComponent::EquipItem(F_InventoryItem* Item)
{
	switch (Item->ItemType)
	{
	case EItemType::EIT_Armour:
		UE_LOG(LogInventoryComponent, Log, TEXT("Equipping the armour set..."));
		SwapEquipped(*Item, EquippedArmour);
		return true;

	case EItemType::EIT_Weapon:
		UE_LOG(LogInventoryComponent, Log, TEXT("Equipping the weapon..."));
		SwapEquipped(*Item, EquippedWeapon);
		return true;

	case EItemType::EIT_None:
	case EItemType::EIT_Miscellaneous:
	case EItemType::EIT_Quest:
	default:
		UE_LOG(LogInventoryComponent, Warning, TEXT("This item cannot be equiped."));
		return false;
	}
}

bool UInventoryComponent::UnequipItem(F_InventoryItem* Item)
{
	UE_LOG(LogInventoryComponent, Log, TEXT("Unequipping the item..."));
	if (ProcessItem(Item, Item->Quantity))
	{
		if (Item->ItemType == EItemType::EIT_Armour)
		{
			EquippedArmour.ClearItem();
		}
		else if (Item->ItemType == EItemType::EIT_Weapon)
		{
			EquippedWeapon.ClearItem();
		}
	}
	return false;
}

bool UInventoryComponent::TransferItem(F_InventoryItem* Item, UInventoryComponent* Receiver, int32 Quantity /*= 1*/)
{
	if (Receiver->ProcessItem(Item, Quantity))
	{
		RemoveItem(Item, Quantity);
		return true;
	}
	UE_LOG(LogInventoryComponent, Error, TEXT("The item cannot be transferred."));
	return false;
}

bool UInventoryComponent::ReceiveItem(F_InventoryItem* Item, UInventoryComponent* Sender, int32 Quantity /*= 1*/)
{
	if (ProcessItem(Item, Quantity))
	{
		Sender->RemoveItem(Item, Quantity);
		return true;
	}
	UE_LOG(LogInventoryComponent, Error, TEXT("The item cannot be received."));
	return false;
}

void UInventoryComponent::SwapEquipped(F_InventoryItem& Item, F_InventoryItem& EquippedItem)
{
	F_InventoryItem* ItemAtLocation = &SetItemsForItemType(Item.ItemType)[Item.IndexLocation];
	F_InventoryItem Temp;
	Temp.ItemClass = EquippedItem.ItemClass;
	Temp.ItemType = EquippedItem.ItemType;
	Temp.Quantity = EquippedItem.Quantity;

	EquippedItem.ItemClass = ItemAtLocation->ItemClass;
	EquippedItem.ItemType = ItemAtLocation->ItemType;
	EquippedItem.Quantity = ItemAtLocation->Quantity;

	ItemAtLocation->ItemClass = Temp.ItemClass;
	ItemAtLocation->ItemType = Temp.ItemType;
	ItemAtLocation->Quantity = Temp.Quantity;
}

const TArray<F_InventoryItem>& UInventoryComponent::GetItemsForItemType(EItemType ItemType) const
{
	switch (ItemType)
	{
	case EItemType::EIT_Armour:
	case EItemType::EIT_Weapon:
		return Equipment;
	case EItemType::EIT_Quest:
		return QuestItems;
	case EItemType::EIT_Consumable:
		return Consumables;
	case EItemType::EIT_Miscellaneous:
		return MiscellaneousItems;
	case EItemType::EIT_None:
	default:
		UE_LOG(LogInventoryComponent, Warning, TEXT("Cannot get the inventory section for an item since the item is of type EIT_None."));
		return Equipment;
	}
}

int UInventoryComponent::FindAvailableLocation(F_InventoryItem* Item)
{
	UE_LOG(LogInventoryComponent, Log, TEXT("Searching for an available location..."));

	// Case 1: There's another Item of the same class present in the inventory and it's quantity is less than the stack size
	UBaseItem* DefaultItem = Cast<UBaseItem>(Item->ItemClass->GetDefaultObject(true));
	if (DefaultItem->bIsStackable)
	{
		for (const F_InventoryItem& Element : GetItemsForItemType(Item->ItemType))
		{
			if (Element.ItemClass == Item->ItemClass)
			{
				if (Element.Quantity < DefaultItem->StackSize)
				{
					UE_LOG(LogInventoryComponent, Log, TEXT("Found an item of the same class at location %d"), Element.IndexLocation);
					return Element.IndexLocation;
				}
			}
		}
	}

	// Case 2: If there's an inventory slot that is currently empty
	for (const F_InventoryItem& Element : GetItemsForItemType(Item->ItemType))
	{
		if (Element.ItemClass == UBaseItem::StaticClass())
		{
			UE_LOG(LogInventoryComponent, Log, TEXT("Found an empty slot at location %d"), Element.IndexLocation);
			return Element.IndexLocation;
		}
	}

	UE_LOG(LogInventoryComponent, Warning, TEXT("No suitable slot found."));
	return -1;
}

TArray<F_InventoryItem>& UInventoryComponent::SetItemsForItemType(EItemType ItemType)
{
	switch (ItemType)
	{
	case EItemType::EIT_Armour:
	case EItemType::EIT_Weapon:
		return Equipment;
	case EItemType::EIT_Quest:
		return QuestItems;
	case EItemType::EIT_Consumable:
		return Consumables;
	case EItemType::EIT_Miscellaneous:
		return MiscellaneousItems;
	case EItemType::EIT_None:
	default:
		UE_LOG(LogInventoryComponent, Warning, TEXT("Cannot get the inventory section for an item since the item is of type EIT_None."));
		return Equipment;
	}
}

void UInventoryComponent::InitialiseInventory()
{
	// Initialise all arrays
	Equipment.SetNum(EquipmentCapacity);
	for (int i = 0; i <= EquipmentCapacity - 1; ++i)
	{
		Equipment[i].ItemClass = UBaseItem::StaticClass();
		Equipment[i].Quantity = 0;
		Equipment[i].OwningInventory = this;
		Equipment[i].IndexLocation = i;
		Equipment[i].ItemType = EItemType::EIT_None;
	}

	QuestItems.SetNum(QuestItemsCapacity);
	for (int i = 0; i <= QuestItemsCapacity - 1; ++i)
	{
		QuestItems[i].ItemClass = UBaseItem::StaticClass();
		QuestItems[i].Quantity = 0;
		QuestItems[i].OwningInventory = this;
		QuestItems[i].IndexLocation = i;
		QuestItems[i].ItemType = EItemType::EIT_None;
	}

	Consumables.SetNum(ConsumablesCapacity);
	for (int i = 0; i <= ConsumablesCapacity - 1; ++i)
	{
		Consumables[i].ItemClass = UBaseItem::StaticClass();
		Consumables[i].Quantity = 0;
		Consumables[i].OwningInventory = this;
		Consumables[i].IndexLocation = i;
		Consumables[i].ItemType = EItemType::EIT_None;
	}

	MiscellaneousItems.SetNum(MiscellaneousItemsCapacity);
	for (int i = 0; i <= MiscellaneousItemsCapacity - 1; ++i)
	{
		MiscellaneousItems[i].ItemClass = UBaseItem::StaticClass();
		MiscellaneousItems[i].Quantity = 0;
		MiscellaneousItems[i].OwningInventory = this;
		MiscellaneousItems[i].IndexLocation = i;
		MiscellaneousItems[i].ItemType = EItemType::EIT_None;
	}

	// Initialise Equipped slots
	EquippedArmour.Quantity = 0;
	EquippedArmour.OwningInventory = this;
	EquippedArmour.IndexLocation = EQ_ARMOUR_INDEX_LOCATION;
	EquippedArmour.ItemClass = UBaseItem::StaticClass();
	EquippedArmour.ItemType = EItemType::EIT_None;

	EquippedWeapon.Quantity = 0;
	EquippedWeapon.OwningInventory = this;
	EquippedWeapon.IndexLocation = EQ_WEAPON_INDEX_LOCATION;
	EquippedWeapon.ItemClass = UBaseItem::StaticClass();
	EquippedWeapon.ItemType = EItemType::EIT_None;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialiseInventory();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
