#pragma once


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