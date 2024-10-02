#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StorageInterface.generated.h"




UINTERFACE(MinimalAPI)
class UStorageInterface : public UInterface
{
	GENERATED_BODY()
};

class INVENTORYSYSTEM_API IStorageInterface
{
	GENERATED_BODY()


public:
	virtual void IntialiseStorage() = 0;

	virtual void GenerateRandomItems() = 0;

	virtual void DisplayContent() = 0;
};