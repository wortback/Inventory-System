// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/F_InventoryItem.h"
#include "InventoryComponent.generated.h"




/**
 * Actor Component that handles all operations related to the player's inventory.
 * 
 * Operations include:
 *		Adding/removing an item to/from the inventory
 *		Equipping/unequipping an item (only applicable for armour sets and weapons)
 *		Transferring items between actors that possess inventory components
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	/** Array for items of types Armour, Weapon */
	TArray<F_InventoryItem> Equipment;

	/** Array for items of type QuestItem */
	TArray<F_InventoryItem> QuestItems;

	/** Array for items of type Consumable */
	TArray<F_InventoryItem> Consumables;

	/** Array for items of type MiscellaneousItem */
	TArray<F_InventoryItem> MiscellaneousItems;

	int32 EquipmentCapacity = 15;

	int32 QuestItemsCapacity = 30;

	int32 ConsumablesCapacity = 30;

	int32 MiscellaneousItemsCapacity = 30;

	/** Inventory item reserved for the equipped armour */
	F_InventoryItem EquippedArmour;

	/** Inventory item reserved for the equipped weapon */
	F_InventoryItem EquippedWeapon;

	/** Inventory item reserved for quick access, such as a hotkey or shortcut slot */
	F_InventoryItem QuickAccessItem1;

	/** Inventory item reserved for quick access, such as a hotkey or shortcut slot */
	F_InventoryItem QuickAccessItem2;

	/** Inventory item reserved for quick access, such as a hotkey or shortcut slot */
	F_InventoryItem QuickAccessItem3;

	/** Inventory item reserved for quick access, such as a hotkey or shortcut slot */
	F_InventoryItem QuickAccessItem4;

public:	
	/** Default Constructor */
	UInventoryComponent();

	/**
	 * Finds an available slot in the inventory to host an item
	 * 
	 * @param Item The item to be processed
	 * @return true if the item was successfully added
	 * @return false if the item could not be added
	 */
	bool ProcessItem(F_InventoryItem* Item, int32 Quantity);

	/**
	 * Removes Item from the inventory
	 *
	 * @param Item The item to be removed
	 * @return true if the removal was successful
	 */
	bool RemoveItem(F_InventoryItem* Item, int32 Quantity);

	/**
	 * Moves the Item from the inventory array to the equipped slot
	 * Only applicable to weapons and armour sets
	 *
	 * @param Item The item to be equipped
	 * @return true if the removal was successful
	 */
	bool EquipItem(F_InventoryItem* Item);

	/**
	 * Moves the Item from the equipped slot to the inventory
	 * Only applicable to weapons and armour sets
	 *
	 * @param Item The item to be unequipped
	 * @return true if the removal was successful
	 */
	bool UnequipItem(F_InventoryItem* Item);

	/**
	 * Moves the Item from this inventory to another one
	 *
	 * @param Item The item to be transferred
	 * @param Receiver The InvenotryComponent that receives the item
	 * @return true if the transfer was successful
	 */
	bool TransferItem(F_InventoryItem* Item, UInventoryComponent* Receiver, int32 Quantity = 1);

	/**
	 * Moves the Item from the sender inventory to this inventory
	 *
	 * @param Item The item to be received
	 * @param Sender The InvenotryComponent that transfers the item
	 * @return true if the transfer was successful
	 */
	bool ReceiveItem(F_InventoryItem* Item, UInventoryComponent* Sender, int32 Quantity = 1);

	/**
	 * Depending on ItemType returns the TArray the item can be assigned to
	 */
	const TArray<F_InventoryItem>& GetItemsForItemType(EItemType ItemType) const;

	/**
	 * Depending on ItemType returns the TArray the item can be assigned to
	 */
	TArray<F_InventoryItem>& SetItemsForItemType(EItemType ItemType);

protected:

	virtual void BeginPlay() override;

private:
	void InitialiseInventory();

	void InitialiseItemArray(TArray<F_InventoryItem>& ItemArr, int32 Capacity);

	void InitialiseEquippedItem(F_InventoryItem& Item, int32 IndexLocation);

	/**
	 * Once an item is added to the inventory, find an available slot to host the item
	 *
	 * @return available index location in the inventory
	 * @return -1, if Item cannot be added
	 */
	int FindAvailableLocation(F_InventoryItem* Item);

	/**
	 * Adds Item to the inventory
	 *
	 * @param Item The item to be added
	 * @param IndexLocation The index of the position in the inventory where the item is to be hosted
	 */
	F_InventoryItem* AddItem(F_InventoryItem* Item, int IndexLocation, int32 Quantity);

	void SwapEquipped(F_InventoryItem& Item, F_InventoryItem& EquippedItem);


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE const TArray<F_InventoryItem>& GetEquipment() const { return Equipment; }
	FORCEINLINE const TArray<F_InventoryItem>& GetQuestItems() const { return QuestItems; }
	FORCEINLINE const TArray<F_InventoryItem>& GetConsumables() const { return Consumables; }
	FORCEINLINE const TArray<F_InventoryItem>& GetMiscellaneousItems() const { return MiscellaneousItems; }

	FORCEINLINE int32 GetEquipmentCapacity() const { return EquipmentCapacity; }
	FORCEINLINE int32 GetQuestItemsCapacity() const { return QuestItemsCapacity; }
	FORCEINLINE int32 GetConsumablesCapacity() const { return ConsumablesCapacity; }
	FORCEINLINE int32 GetMiscellaneousItemsCapacity() const { return MiscellaneousItemsCapacity; }

	FORCEINLINE const F_InventoryItem& GetEquippedArmour() const { return EquippedArmour; }
	FORCEINLINE const F_InventoryItem& GetEquippedWeapon() const { return EquippedWeapon; }

	const F_InventoryItem& GetQuickAccessItem(int32 QAIndex) const;
		
};
