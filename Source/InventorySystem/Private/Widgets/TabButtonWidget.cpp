// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/TabButtonWidget.h"
#include "Widgets/BaseButton.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/InteractHUDInterface.h"
#include "Widgets/InventoryWidget.h"
#include "GameFramework/Character.h"




void UTabButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EquipmentTabButton->OnClicked.AddDynamic(this, &UTabButtonWidget::OnEquipmentTabClicked);
	QuestTabButton->OnClicked.AddDynamic(this, &UTabButtonWidget::OnQuestTabClicked);
	ConsumableTabButton->OnClicked.AddDynamic(this, &UTabButtonWidget::OnConsumableTabClicked);
	MiscTabButton->OnClicked.AddDynamic(this, &UTabButtonWidget::OnMiscTabClicked);

}

void UTabButtonWidget::OnEquipmentTabClicked()
{
// 	if (OwningWidget)
// 	{
// 		OwningWidget->SetCurrentTab(EInventoryWidgetTab::EIWT_Equipment);
// 		UpdateInventoryHUD();
// 	}
// 	else
// 	{
// 		UE_LOG(LogInventoryHUD, Warning, TEXT("OwningWidget for UTabButtonWidget is NULL."));
// 	}
}

void UTabButtonWidget::OnQuestTabClicked()
{

// 	if (OwningWidget)
// 	{
// 		OwningWidget->SetCurrentTab(EInventoryWidgetTab::EIWT_Quest);
// 		UpdateInventoryHUD();
// 	}
// 	else
// 	{
// 		UE_LOG(LogInventoryHUD, Warning, TEXT("OwningWidget for UTabButtonWidget is NULL."));
// 	}
}

void UTabButtonWidget::OnConsumableTabClicked()
{
// 	if (OwningWidget)
// 	{
// 		OwningWidget->SetCurrentTab(EInventoryWidgetTab::EIWT_Consumable);
// 		UpdateInventoryHUD();
// 	}
// 	else
// 	{
// 		UE_LOG(LogInventoryHUD, Warning, TEXT("OwningWidget for UTabButtonWidget is NULL."));
// 	}
}

void UTabButtonWidget::OnMiscTabClicked()
{
// 	if (OwningWidget)
// 	{
// 		OwningWidget->SetCurrentTab(EInventoryWidgetTab::EIWT_Miscellaneous);
// 		UpdateInventoryHUD();
// 	}
// 	else
// 	{
// 		UE_LOG(LogInventoryHUD, Warning, TEXT("OwningWidget for UTabButtonWidget is NULL."));
// 	}
}

void UTabButtonWidget::UpdateInventoryHUD()
{
	ACharacter* PlayerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter)
	{
		IInteractHUDInterface* Interface = Cast<IInteractHUDInterface>(PlayerCharacter);
		if (Interface)
		{
			Interface->UpdateInventoryHUD();
		}
		else
		{
			UE_LOG(LogInventoryHUD, Warning, TEXT("Interface Cast unsuccessful"));
		}
	}
}
