// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InventoryWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/TabButtonWidget.h"
#include "Widgets/PlayerInventoryWindow.h"

//Logging
#include "InventorySystem.h"

void UInventoryWidget::UpdateMenu()
{
	PlayerInventoryWindow->UpdateMenu();
}
