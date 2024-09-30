// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/TabButtonWidget.h"


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

void UInventoryWidget::UpdateMenu()
{
	CurrentTab = TabSwitch->GetCurrentTab();

	switch (CurrentTab)
	{
	case EInventoryWidgetTab::EIWT_Equipment:
		TabName->SetText(FText::FromString("EQUIPMENT"));
		break;
	case EInventoryWidgetTab::EIWT_Quest:
		TabName->SetText(FText::FromString("QUEST ITEMS"));
		break;
	case EInventoryWidgetTab::EIWT_Consumable:
		TabName->SetText(FText::FromString("CONSUMABLES"));
		break;
	case EInventoryWidgetTab::EIWT_Miscellaneous:
		TabName->SetText(FText::FromString("MISC"));
		break;
	default:
		UE_LOG(LogInventoryHUD, Error, TEXT("Cannot update menu! Invalid current tab!"));
		break;
	}
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TabName->SetText(FText::FromString("EQUIPMENT"));
	UpdateMenu();
}
