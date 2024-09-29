// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"
#include "Interfaces/InteractHUDInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"



UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::UpdateInventoryHUD()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		IInteractHUDInterface* Interface = Cast<IInteractHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			Interface->UpdateInventoryHUD(this);
		}

	}
}

bool UInventoryComponent::ProcessItem(F_InventoryItem* Item)
{
	int ItemIndexLocation = FindAvailableLocation(Item);
	UE_LOG(LogTemp, Warning, TEXT("Found available location at Index %d"), ItemIndexLocation);
	if (ItemIndexLocation >= 0)
	{
		F_InventoryItem* AddedItem = AddItem(Item, ItemIndexLocation);
		if (AddedItem->Quantity > 0)
		{
			ProcessItem(AddedItem);
		}
		else
		{
			return true;
		}
		delete AddedItem;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory is full"));
		return false;
	}


	return false;
}

F_InventoryItem* UInventoryComponent::AddItem(F_InventoryItem* Item, int IndexLocation)
{
	F_InventoryItem* ItemAtLocation = &Items[IndexLocation];
	UBaseItem* DefaultItem = Cast<UBaseItem>(UBaseItem::StaticClass()->GetDefaultObject(true));
	int NewQuantity = ItemAtLocation->Quantity + Item->Quantity;

	int QuantityClamped = FMath::Clamp(NewQuantity, 0, DefaultItem->StackSize);
	int DeltaQuantity = NewQuantity - QuantityClamped;

	UE_LOG(LogTemp, Warning, TEXT("NewQuantity %d"), NewQuantity);
	UE_LOG(LogTemp, Warning, TEXT("QuantityClamped %d"), QuantityClamped);
	UE_LOG(LogTemp, Warning, TEXT("DeltaQuantity %d"), DeltaQuantity);

	// Update member variables on the item st this particular slot
	ItemAtLocation->Quantity = QuantityClamped;
	ItemAtLocation->ItemClass = Item->ItemClass;
	ItemAtLocation->OwningInventory = this;
	ItemAtLocation->IndexLocation = IndexLocation;

	// A new F_InventoryItem Object that stores DeltaQuantity
	// if it is bigger than 0, will attempt to store the remaining copies of the item in a separate slot
	F_InventoryItem* Result = new F_InventoryItem(*Item);
	Result->Quantity = DeltaQuantity;

	return Result;
}

bool UInventoryComponent::RemoveItem(F_InventoryItem* Item)
{
	F_InventoryItem* ItemAtLocation = &Items[Item->IndexLocation];
	ItemAtLocation->ItemClass = UBaseItem::StaticClass();
	ItemAtLocation->OwningInventory = nullptr;
	ItemAtLocation->Quantity = 0;

	return true;
}


int UInventoryComponent::FindAvailableLocation(F_InventoryItem* Item)
{
	// Case 1: There's another Item of the same class present in the inventory and it's quantity is less than the stack size
	for (F_InventoryItem Element : Items)
	{
		if (Element.ItemClass == Item->ItemClass)
		{
			UBaseItem* DefaultItem = Cast<UBaseItem>(UBaseItem::StaticClass()->GetDefaultObject(true));
			if (Element.Quantity < DefaultItem->StackSize)
			{
				return Element.IndexLocation;
			}
		}
	}

	// Case 2: If there's an inventory slot that is currently empty
	for (F_InventoryItem Element : Items)
	{
		if (Element.ItemClass == UBaseItem::StaticClass())
		{
			return Element.IndexLocation;
		}
	}
	return -1;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Items.SetNum(Capacity);
	for (int i = 0; i <= Capacity - 1; ++i)
	{
		Items[i].Quantity = 0;
		Items[i].OwningInventory = this;
		Items[i].IndexLocation = i;
	}
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

