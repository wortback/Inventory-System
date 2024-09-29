// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WorldItem.h"
#include "Components/BillboardComponent.h"
#include "Inventory/InventoryComponent.h"

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
	Item->ItemClass = ItemClass;
	Item->Quantity = Quantity;
	if (Inventory->ProcessItem(Item))
	{
		UE_LOG(LogTemp, Warning, TEXT("Handle successful item processing."));
		Destroy();
		return true;
	}
	else
	{
		return false;
	}
	
}

