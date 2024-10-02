// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WorldItem.h"
#include "Components/BillboardComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Items/BaseItem.h"

// Logging
#include "InventorySystem.h"



// Sets default values
AWorldItem::AWorldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));

	SetRootComponent(DefaultSceneComponent);
	Billboard->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWorldItem::BeginPlay()
{
	Super::BeginPlay();

	// Set Despawn Timer
	if (ItemClass)
	{
		UBaseItem* Item = Cast<UBaseItem>(ItemClass->GetDefaultObject(true));
		if (Item)
		{
			if (Item->bShouldDie)
			{
				SetDespawnTimer();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemClass is empty"));
		//TODO
		// ItemClass is empty at this point so DespawnTimer isn't set properly
	}
	
}

void AWorldItem::PreInitializeComponents()
{
	if (ItemClass)
	{
		UBaseItem* Item = Cast<UBaseItem>(ItemClass->GetDefaultObject(true));
		if (Item)
		{
			Mesh->SetStaticMesh(Item->DisplayMesh);
			DespawnTime = Item->DespawnTime;
		}
	}
	
}


void AWorldItem::SetDespawnTimer()
{
	SetLifeSpan(DespawnTime);
}

// Called every frame
void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AWorldItem::Interact(UInventoryComponent* Inventory)
{
	F_InventoryItem* Item = new F_InventoryItem();
	if (ItemClass)
	{
		UBaseItem* BaseItem = Cast<UBaseItem>(ItemClass->GetDefaultObject());

		if (BaseItem)
		{
			Item->ItemClass = ItemClass;
			Item->Quantity = Quantity;

			UE_LOG(LogItems, Log, TEXT("Interacting with the item of type %s"), *(EItemTypeToString(BaseItem->ItemType)));
			Item->ItemType = BaseItem->ItemType;
		}

		if (Inventory->ProcessItem(Item))
		{
			UE_LOG(LogItems, Log, TEXT("Handle successful item processing."));
			Destroy();
			return true;
		}
		else
		{
			return false;
		}
	}
	UE_LOG(LogItems, Warning, TEXT("ItemClass is not set for this WorldObject! Failed to interact."));
	return false;
}

