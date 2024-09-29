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
	/** Capacity of the inventory */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 Capacity = 10;
	
	/** Array of items that are stored in the inventory */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<F_InventoryItem> Items;

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
	 * Adds Item to the inventory
	 * 
	 * @param Item The item to be added
	 * @param IndexLocation The index of the position in the inventory where the item is to be hosted
	 */
	F_InventoryItem* AddItem(F_InventoryItem* Item, int IndexLocation);

	/**
	 * Removes Item from the inventory
	 *
	 * @param Item The item to be removed
	 * @return true if the removal was successful
	 */
	bool RemoveItem(F_InventoryItem* Item);

	/**
	 * Once an item is added to the inventory, find an available slot to host the item
	 * 
	 * @return available index location in the inventory
	 * @return -1, if Item cannot be added	
	 */
	int FindAvailableLocation(F_InventoryItem* Item);


protected:

	virtual void BeginPlay() override;



public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE int GetCapacity() const { return Capacity; }
	FORCEINLINE const TArray<F_InventoryItem>& GetItems() const { return Items; }
		
};
