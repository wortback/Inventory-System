// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseMiscItem.h"
#include "System/CommonTypes.h"

UBaseMiscItem::UBaseMiscItem()
{
	bIsStackable = false;
	ItemType = EItemType::EIT_Miscellaneous;
}
