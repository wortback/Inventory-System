// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/F_InventoryItem.h"

#include "StorageContentSlot.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UStorageContentSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> UseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> SlotText;

	F_InventoryItem* SlotItem;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClicked();

};
