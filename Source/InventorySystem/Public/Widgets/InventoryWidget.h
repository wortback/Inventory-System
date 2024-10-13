// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/CommonTypes.h"
#include "InventoryWidget.generated.h"





class UWrapBox;
class UTextBlock;
class UTabButtonWidget;
class UInventorySlot;
class UPlayerInventoryWindow;


/**
 * Widget that displays the content of InventoryComponent, namely contains the corresponding slots of 4 items arrays.
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UPlayerInventoryWindow> PlayerInventoryWindow;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> EquippedArmour;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UInventorySlot> EquippedWeapon;

public:
	void UpdateMenu();
};
