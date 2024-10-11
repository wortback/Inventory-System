// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/F_InventoryItem.h"
#include "InventoryComponent.generated.h"





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

	/** Separate slot for the equipped armour set */
	F_InventoryItem EquippedArmour;

	/** Separate slot for the equipped weapon */
	F_InventoryItem EquippedWeapon;

public:	
	/** Default Constructor */
	UInventoryComponent();

	/**
	 * Updates the slots in the inventory HUD
	 */
	void UpdateInventoryHUD();

	/**
	 * Finds an available slot in the inventory to host an item
	 * 
	 * @param Item The item to be processed
	 * @return true if the item was successfully added
	 * @return false if the item could not be added
	 */
	bool ProcessItem(F_InventoryItem* Item);

	/**
	 * Removes Item from the inventory
	 *
	 * @param Item The item to be removed
	 * @return true if the removal was successful
	 */
	bool RemoveItem(F_InventoryItem* Item);

	/**
	 * Moves the Item from the inventory array to the equipped slot
	 * Only applicable to weapons and armour sets
	 *
	 * @param Item The item to be equipped
	 * @return true if the removal was successful
	 */
	bool EquipItem(F_InventoryItem* Item);

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
	F_InventoryItem* AddItem(F_InventoryItem* Item, int IndexLocation);

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
		
};
