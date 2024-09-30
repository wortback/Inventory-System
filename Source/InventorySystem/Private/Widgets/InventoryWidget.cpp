// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"


DEFINE_LOG_CATEGORY(LogInventoryHUD);


EItemType UInventoryWidget::GetItemTypeForCurrentTab()
{
	switch (CurrentTab)
	{
	case EInventoryWidgetTab::EIWT_Equipment:
		return EItemType::EIT_Armour;
		break;
	case EInventoryWidgetTab::EIWT_Quest:
		return EItemType::EIT_Quest;
		break;
	case EInventoryWidgetTab::EIWT_Consumable:
		return EItemType::EIT_Consumable;
		break;
	case EInventoryWidgetTab::EIWT_Miscellaneous:
		return EItemType::EIT_Miscellaneous;
		break;
	default:
		UE_LOG(LogInventoryHUD, Error, TEXT("Cannot get ItemType. Invalid current tab!"));
		return EItemType::EIT_None;
		break;
	}
}
