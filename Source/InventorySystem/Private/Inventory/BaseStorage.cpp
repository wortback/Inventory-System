// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/BaseStorage.h"
#include "Inventory/F_InventoryItem.h"
#include "Components/StaticMeshComponent.h"
#include "Widgets/StorageContentWidget.h"
#include "Widgets/StorageContentSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Items/BaseConsumable.h"
#include "Components/WrapBox.h"

// Logging
#include "InventorySystem.h"


// Sets default values
ABaseStorage::ABaseStorage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DisplayMesh"));

	SetRootComponent(DefaultSceneComponent);
	DisplayMesh->SetupAttachment(RootComponent);

	IntialiseStorage();
}

// Called when the game starts or when spawned
void ABaseStorage::BeginPlay()
{
	Super::BeginPlay();

	RuntimeItems = OriginalItems;
}

void ABaseStorage::IntialiseStorage()
{
	OriginalItems.SetNum(Capacity);
	for (int i = 0; i <= Capacity - 1; ++i)
	{
		OriginalItems[i].Quantity = 0;
		OriginalItems[i].IndexLocation = i;
		OriginalItems[i].ItemType = EItemType::EIT_None;
		OriginalItems[i].ItemClass = UBaseItem::StaticClass();
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
		UE_LOG(LogInventoryHUD, Log, TEXT("%d: type %s"), i, *EItemTypeToString(RuntimeItems[i].ItemType));
		UE_LOG(LogInventoryHUD, Log, TEXT("%d: quantity %d"), i, RuntimeItems[i].Quantity);
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ContentWidget = CreateWidget<UStorageContentWidget>(PlayerController, ContentWidgetClass);
		if (ContentWidget)
		{
			UE_LOG(LogInventoryHUD, Log, TEXT("Contents of the interacting storage actor are displayed."));
			ContentWidget->OwningStorage = this;

			for (F_InventoryItem& Item : RuntimeItems)
			{
				if (Item.ItemType != EItemType::EIT_None && ContentSlotClass)
				{
					UStorageContentSlot* ChildSlot = CreateWidget<UStorageContentSlot>(GetWorld(), ContentSlotClass);
					ChildSlot->SlotItem = &Item;

					ContentWidget->SlotBox->AddChildToWrapBox(ChildSlot);
				}
			}
			
			ContentWidget->AddToViewport();
			ContentWidget->SetPositionInViewport(FVector2D(300, 300));

			PlayerController->bShowMouseCursor = true;
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetWidgetToFocus(ContentWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);
		}
	}
}

void ABaseStorage::HideContent()
{
	if (ContentWidget)
	{
		ContentWidget->RemoveFromParent();
		ContentWidget = nullptr;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
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

