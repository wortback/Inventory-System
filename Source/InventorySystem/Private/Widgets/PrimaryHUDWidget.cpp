// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PrimaryHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Widgets/InventorySlot.h"
#include "Components/WrapBox.h"
#include "Inventory/InventoryComponent.h"
#include "Widgets/PlayerInventoryWindow.h"
#include "Widgets/TransferItemsWidget.h"
#include "System/Defines.h"

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

void UPrimaryHUDWidget::ShowNPCInventory(bool bShowInventory)
{
	if (bShowInventory)
	{
		PlayerInventory->SetVisibility(ESlateVisibility::Visible);
		NPCInventory->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerInventory->SetVisibility(ESlateVisibility::Collapsed);
		NPCInventory->SetVisibility(ESlateVisibility::Collapsed);

		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Character)
		{
			IInventoryHUDInterface* Interface = Cast<IInventoryHUDInterface>(Character);
			if (Interface)
			{
				Interface->UpdateNPCComponentPtr(nullptr);
			}
		}
	}
}

void UPrimaryHUDWidget::UpdateInventory(const UInventoryComponent* InventoryComponent)
{
	if (InventoryComponent && InventorySlotClass)
	{
		InventoryMenu->UpdateMenu();
		UE_LOG(LogInventoryHUD, Log, TEXT("Current tab is %d"), InventoryMenu->PlayerInventoryWindow->GetItemTypeForCurrentTab());
		InventoryMenu->PlayerInventoryWindow->InventoryBox->ClearChildren();
		
		for (const F_InventoryItem& Item : InventoryComponent->GetItemsForItemType(InventoryMenu->PlayerInventoryWindow->GetItemTypeForCurrentTab()))
		{
			UInventorySlot* ChildSlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
			ChildSlot->Item = Item;
			ChildSlot->OwningHUD = this;
			InventoryMenu->PlayerInventoryWindow->InventoryBox->AddChildToWrapBox(ChildSlot);
		}

		//InventoryMenu->QuickSlot1, InventoryMenu->QuickSlot2, InventoryMenu->QuickSlot3, InventoryMenu->QuickSlot4
		TArray<TObjectPtr<UInventorySlot>> EquippedSlots = { InventoryMenu->EquippedArmour, InventoryMenu->EquippedWeapon };
		TArray<TObjectPtr<UInventorySlot>> QASlots = { InventoryMenu->QuickSlot1, InventoryMenu->QuickSlot2, 
													   InventoryMenu->QuickSlot3, InventoryMenu->QuickSlot4 };
		TArray<const F_InventoryItem*> EquippedItems = { &InventoryComponent->GetEquippedArmour(), &InventoryComponent->GetEquippedWeapon() };
		for (int32 i = 0; i < EquippedSlots.Num(); ++i)
		{
			UpdateEquippedAndQASlots(EquippedSlots[i], EquippedItems[i]);
		}
		for (int32 i = 0; i < EquippedSlots.Num(); ++i)
		{
			UpdateEquippedAndQASlots(QASlots[i], &InventoryComponent->GetQuickAccessItem(i+1));
		}

	}
	else
	{
		UE_LOG(LogInventoryHUD, Warning, TEXT("Cannot update the inventory. InventoryComponent is NULL or InventorySlotClass is not set in PrimaryHUD."));
	}
}

void UPrimaryHUDWidget::UpdateEquippedAndQASlots(TObjectPtr<UInventorySlot> InventorySlot, const F_InventoryItem* Item)
{
	InventorySlot->Item = *Item;
	InventorySlot->OwningHUD = this;
	InventorySlot->UpdateSlotContent();
}

void UPrimaryHUDWidget::UpdateInventory(const UInventoryComponent* PlayerComp, const UInventoryComponent* NPCComp)
{
	if (PlayerComp && NPCComp && InventorySlotClass)
	{
		PlayerInventory->UpdateMenu();
		NPCInventory->UpdateMenu();
		PlayerInventory->InventoryBox->ClearChildren();
		NPCInventory->InventoryBox->ClearChildren();

		for (const F_InventoryItem& Item : PlayerComp->GetItemsForItemType(PlayerInventory->GetItemTypeForCurrentTab()))
		{
			UInventorySlot* ChildSlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
			ChildSlot->Item = Item;
			ChildSlot->OwningHUD = this;
			PlayerInventory->InventoryBox->AddChildToWrapBox(ChildSlot);
		}

		for (const F_InventoryItem& Item : NPCComp->GetItemsForItemType(NPCInventory->GetItemTypeForCurrentTab()))
		{
			UInventorySlot* ChildSlot = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotClass);
			ChildSlot->Item = Item;
			ChildSlot->OwningHUD = this;
			NPCInventory->InventoryBox->AddChildToWrapBox(ChildSlot);
		}
	}
	else
	{
		UE_LOG(LogInventoryHUD, Warning, TEXT("Cannot update the inventory. Either PlayerComp or NPCComp is NULL or InventorySlotClass is not set in PrimaryHUD."));
	}
}

void UPrimaryHUDWidget::CloseInventory()
{
	// Don't do anything, if the widget is collapsed
	if (InventoryMenu->GetVisibility() == ESlateVisibility::Visible)
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

	if (NPCInventory->GetVisibility() == ESlateVisibility::Visible)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;

			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}

		ShowNPCInventory(false);
	}
}

FReply UPrimaryHUDWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FName Key = InKeyEvent.GetKey().GetFName();
	if (Key == "Tab" || Key == "Escape")
    {
		CloseInventory();
    }
	
	else if (Key == "D" || Key == "E")
	{
		if (OverSlot)
		{
			ExecuteKeyBinding(Key);
		}
	}
	return FReply::Handled();
}

void UPrimaryHUDWidget::ExecuteKeyBinding(FName Key)
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		IInventoryHUDInterface* Interface = Cast<IInventoryHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			if (Key == "D")
			{
				Interface->RemoveItem(&(OverSlot->Item), 1);
			}
			else if (Key == "E")
			{
				ExecuteEKey(Interface);
			}
			Interface->UpdateInventoryHUD();
		}
	}
}

void UPrimaryHUDWidget::ExecuteEKey(IInventoryHUDInterface* Interface)
{
	// If the character is not trading:
	if (!Interface->GetIsInTradeMode())
	{
		if (InventoryMenu->IsSpecialSlotIndex(OverSlot->Item.IndexLocation))
		{
			Interface->UnequipItem(&(OverSlot->Item));
		}
		else
		{
			Interface->EquipItem(&(OverSlot->Item));
		}
	}
	// If the character is trading:
	else
	{
		if (OverSlot->Item.Quantity < MIN_REQUIRED_FOR_SLIDER)
		{
			// Is this item located in the character's inventory?
			if (OverSlot->Item.OwningInventory == Interface->GetInventoryComponent())
			{
				Interface->SellItem(&(OverSlot->Item), 1);
			}
			// Or NPC's?
			else
			{
				Interface->BuyItem(&(OverSlot->Item), 1);
			}
		}
		else
		{
			TransferItemsWidget = CreateWidget<UTransferItemsWidget>(GetWorld(), TransferItemsWidgetClass);
			if (TransferItemsWidget)
			{
				TransferItemsWidget->FOnSliderValueConfirmedDelegate.AddDynamic(this, &UPrimaryHUDWidget::HandleSliderValueConfirmed);
				TransferItemsWidget->SetMaxValue(OverSlot->Item.Quantity);
				TransferItemsWidget->SetItemSlot(OverSlot);
				TransferItemsWidget->SetPositionInViewport(FVector2D(500, 500));
				TransferItemsWidget->AddToViewport();
				TransferItemsWidget->SetFocus();
			}
		}	
	}
}

void UPrimaryHUDWidget::HandleSliderValueConfirmed(int32 SliderValue)
{

	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		IInventoryHUDInterface* Interface = Cast<IInventoryHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			// Is this item located in the character's inventory?
			if (TransferItemsWidget->GetItemSlot()->Item.OwningInventory == Interface->GetInventoryComponent())
			{
				Interface->SellItem(&(TransferItemsWidget->GetItemSlot()->Item), SliderValue);
			}
			// Or NPC's?
			else
			{
				Interface->BuyItem(&(TransferItemsWidget->GetItemSlot()->Item), SliderValue);
			}

			Interface->UpdateInventoryHUD();
		}
	}

	// Set focus on the primary HUD again (TODO: It's not working)
	SetFocus();
}

void UPrimaryHUDWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	if (!TransferItemsWidget)
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
}

void UPrimaryHUDWidget::UpdateSlotUnderCursor(UInventorySlot* SlotUnderCursor)
{
	OverSlot = SlotUnderCursor;
}
