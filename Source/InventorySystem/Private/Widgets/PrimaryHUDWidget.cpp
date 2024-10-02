// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PrimaryHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Widgets/InventorySlot.h"
#include "Interfaces/InteractHUDInterface.h"
#include "Components/WrapBox.h"
#include "Inventory/InventoryComponent.h"

// Logging
#include "InventorySystem.h"



void UPrimaryHUDWidget::ShowPlayerInventory(bool bShowInventory)
{
	if (bShowInventory)
	{
		InventoryMenu->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UPrimaryHUDWidget::UpdateInventory(const UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent && InventorySlotClass)
	{
		InventoryMenu->UpdateMenu();
		UE_LOG(LogInventoryHUD, Log, TEXT("Current tab is %d"), InventoryMenu->GetItemTypeForCurrentTab());
		InventoryMenu->InventoryBox->ClearChildren();
	
		for (const F_InventoryItem& Item : InventoryComponent->GetItemsForItemType(InventoryMenu->GetItemTypeForCurrentTab()))
		{
			UInventorySlot* ChildSlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
			ChildSlot->Item = Item;
			ChildSlot->OwningHUD = this;
			InventoryMenu->InventoryBox->AddChildToWrapBox(ChildSlot);
		}
	}
	else
	{
		UE_LOG(LogInventoryHUD, Warning, TEXT("Cannot update the inventory. InventoryComponent is NULL or InventorySlotClass is not set in PrimaryHUD."));
	}
}

void UPrimaryHUDWidget::ClosePlayerInventory()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}

	ShowPlayerInventory(false);

}

FReply UPrimaryHUDWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey().GetFName() == "Tab" || InKeyEvent.GetKey().GetFName() == "Escape")
    {
		ClosePlayerInventory();
    }
	else if (InKeyEvent.GetKey().GetFName() == "D")
	{
		if (OverSlot)
		{
			ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			if (PlayerCharacter)
			{
				IInteractHUDInterface* Interface = Cast<IInteractHUDInterface>(PlayerCharacter);
				if (Interface)
				{
					UE_LOG(LogTemp, Warning, TEXT("Interface Cast sccessful"));
					Interface->RemoveItem(&(OverSlot->Item));
					
					if (OverSlot->Item.OwningInventory)
					{
						Interface->UpdateInventoryHUD(OverSlot->Item.OwningInventory);
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Interface Cast unsuccessful"));
				}
			}
		}
	}
	return FReply::Handled();
}

void UPrimaryHUDWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
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

void UPrimaryHUDWidget::UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor)
{
	OverSlot = SlotUnderCursor;
}
