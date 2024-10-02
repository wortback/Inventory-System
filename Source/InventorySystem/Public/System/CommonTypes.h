#pragma once


#include "CoreMinimal.h"
#include "CommonTypes.generated.h"

UENUM()
enum class EItemType : uint8
{
	EIT_Armour,
    EIT_Weapon,
	EIT_Quest,
	EIT_Consumable,
    EIT_Miscellaneous,
    EIT_None
};

UENUM()
enum class EInventoryWidgetTab : uint8
{
	EIWT_Equipment,
	EIWT_Quest,
	EIWT_Consumable,
    EIWT_Miscellaneous,
};

static FString EItemTypeToString(EItemType ItemType)
{
	switch (ItemType)
	{
	case EItemType::EIT_Armour:
		return FString("EIT_Armour");
		break;
	case EItemType::EIT_Weapon:
		return FString("EIT_Weapon");
		break;
	case EItemType::EIT_Quest:
		return FString("EIT_Quest");
		break;
	case EItemType::EIT_Consumable:
		return FString("EIT_Consumable");
		break;
	case EItemType::EIT_Miscellaneous:
		return FString("EIT_Miscellaneous");
		break;
	case EItemType::EIT_None:
	default:
		return FString("EIT_None");
		break;
	}
}