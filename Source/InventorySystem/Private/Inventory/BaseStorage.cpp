// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/BaseStorage.h"
#include "Inventory/F_InventoryItem.h"
#include "Components/StaticMeshComponent.h"
#include "Widgets/StorageContentWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Items/BaseConsumable.h"

// Logging
#include "InventorySystem.h"


// Sets default values
ABaseStorage::ABaseStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));
	DisplayMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseStorage::BeginPlay()
{
	Super::BeginPlay();

	IntialiseStorage();
}

void ABaseStorage::IntialiseStorage()
{
	Items.SetNum(Capacity);
	for (int i = 0; i <= Capacity - 1; ++i)
	{
		Items[i].Quantity = 0;
		Items[i].IndexLocation = i;
		Items[i].ItemType = EItemType::EIT_None;
	}
}

void ABaseStorage::GenerateRandomItems()
{
	// TODO
}

void ABaseStorage::DisplayContent()
{
	for (int i = 0; i <= Capacity -1; ++i)
	{
		UE_LOG(LogInventoryHUD, Log, TEXT("%d: type %s"), i, *EItemTypeToString(Items[i].ItemType));
		UE_LOG(LogInventoryHUD, Log, TEXT("%d: quantity %d"), i, Items[i].Quantity);
	}


	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ContentWidget = CreateWidget<UStorageContentWidget>(PlayerController, ContentWidgetClass);
		if (ContentWidget)
		{
			UE_LOG(LogInventoryHUD, Log, TEXT("Contents of the interacting storage actor are displayed."));
			ContentWidget->OwningStorage = this;
			
			ContentWidget->AddToViewport();
			ContentWidget->SetPositionInViewport(FVector2D(300, 300));
		}
	}


}

bool ABaseStorage::Interact(UInventoryComponent* Inventory)
{
	UE_LOG(LogInventoryHUD, Log, TEXT("Intarect for BaseStorage is called."));
	DisplayContent();

	return true;
}

// Called every frame
void ABaseStorage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

