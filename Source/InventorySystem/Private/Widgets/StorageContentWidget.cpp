// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/StorageContentWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/BaseStorage.h"
#include "Widgets/StorageContentSlot.h"
#include "Inventory/F_InventoryItem.h"
#include "Items/BaseItem.h"
#include "Items/BaseConsumable.h"
#include "System/CommonTypes.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"

// Logging
#include "InventorySystem.h"




void UStorageContentWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStorageContentWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		if (PlayerController->bShowMouseCursor)
		{
			SetFocus();
		}
	}
}

FReply UStorageContentWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().GetFName() == "Tab" || InKeyEvent.GetKey().GetFName() == "Escape")
	{
		if (OwningStorage)
		{
			OwningStorage->HideContent();
		}
		else
		{
			UE_LOG(LogInventoryHUD, Warning, TEXT("Owning storage is NULL for the ContentWidget."));
		}
	}
	return FReply::Handled();

}

void UStorageContentWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// If all slots are removed (all items taken), remove the widget
	if (!SlotBox->HasAnyChildren())
	{
		OwningStorage->HideContent();
	}
}


