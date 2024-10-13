#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractHUDInterface.generated.h"


class AActor;
class UInventoryComponent;
struct F_InventoryItem;


UINTERFACE(MinimalAPI)
class UInteractHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEM_API IInteractHUDInterface
{
	GENERATED_BODY()
	

public:
	virtual AActor* LookAt() = 0;

	virtual void OpenPlayerInventory() = 0;

	virtual void OpenNPCInventory(UInventoryComponent* NPCInventoryComponent) = 0;

	virtual void UpdateInventoryHUD() = 0;

	virtual void UpdateInventoryHUD(UInventoryComponent* InventoryComponent) = 0;

	virtual void UpdateInventoryHUD(UInventoryComponent* PlayerComp, UInventoryComponent* NPCComp) = 0;

	virtual void RemoveItem(F_InventoryItem* Item) = 0;

	virtual bool ProcessItem(F_InventoryItem* Item) = 0;

	virtual bool EquipItem(F_InventoryItem* Item) = 0;

	virtual void UpdateNPCComponentPtr(UInventoryComponent* InventoryComp) = 0;
};