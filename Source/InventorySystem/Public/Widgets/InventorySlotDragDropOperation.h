// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Interfaces/InventoryWidgetsInterface.h"
#include "InventorySlotDragDropOperation.generated.h"


class UInventorySlot;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventorySlotDragDropOperation : public UDragDropOperation, public IInventoryWidgetsInterface
{
	GENERATED_BODY()
	
	UInventorySlot* UnderDragSlot;

public:
	virtual void UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor) override;

};
