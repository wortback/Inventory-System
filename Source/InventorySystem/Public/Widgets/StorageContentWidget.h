// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StorageContentWidget.generated.h"


class UWrapBox;
class ABaseStorage;
struct F_InventoryItem;
class UStorageContentSlot;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UStorageContentWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** WrapBox that contains slots that represent the items stored in the storage that spawns the widget */
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UWrapBox> SlotBox;

	/** Storage Actor that spawned this widget */
	UPROPERTY(EditAnywhere, Category = "Storage")
	TSubclassOf<ABaseStorage> OwningStorageClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UStorageContentSlot> ContentSlotClass;

	ABaseStorage* OwningStorage = nullptr;
public:
	virtual void NativeConstruct() override;


};
