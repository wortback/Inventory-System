// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PrimaryHUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Widgets/InventorySlot.h"
#include "Interfaces/InteractHUDInterface.h"
#include "Components/WrapBox.h"
#include "Inventory/InventoryComponent.h"
#include "Widgets/PlayerInventoryWindow.h"

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
			IInteractHUDInterface* Interface = Cast<IInteractHUDInterface>(Character);
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

		InventoryMenu->EquippedArmour->Item = InventoryComponent->GetEquippedArmour();
		InventoryMenu->EquippedArmour->OwningHUD = this;
		InventoryMenu->EquippedArmour->UpdateSlotContent();

		InventoryMenu->EquippedWeapon->Item = InventoryComponent->GetEquippedWeapon();
		InventoryMenu->EquippedWeapon->OwningHUD = this;
		InventoryMenu->EquippedWeapon->UpdateSlotContent();
	}
	else
	{
		UE_LOG(LogInventoryHUD, Warning, TEXT("Cannot update the inventory. InventoryComponent is NULL or InventorySlotClass is not set in PrimaryHUD."));
	}
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

void UPrimaryHUDWidget::CloseNPCInventory()
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

FReply UPrimaryHUDWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FName Key = InKeyEvent.GetKey().GetFName();
	if (Key == "Tab" || Key == "Escape")
    {
		ClosePlayerInventory();
		CloseNPCInventory();
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
		IInteractHUDInterface* Interface = Cast<IInteractHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			if (Key == "D")
			{
				Interface->RemoveItem(&(OverSlot->Item));
			}
			else if (Key == "E")
			{
				Interface->EquipItem(&(OverSlot->Item));
				if (OverSlot->Item.OwningInventory == Interface->GetInventoryComponent())
				{
					Interface->SellItem(&(OverSlot->Item));
				}
				else
				{
					Interface->BuyItem(&(OverSlot->Item));
				}
				
			}
			Interface->UpdateInventoryHUD();
		}
	}
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
