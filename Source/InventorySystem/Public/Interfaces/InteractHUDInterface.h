#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractHUDInterface.generated.h"


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
	virtual void OpenPlayerInventory() = 0;

	virtual void UpdateInventoryHUD(UInventoryComponent* Inventoryomponent) = 0;

	virtual void UpdateInventoryHUD() = 0;

	virtual void RemoveItem(F_InventoryItem* Item) = 0;
};