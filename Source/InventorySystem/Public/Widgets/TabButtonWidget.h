// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "System/CommonTypes.h"

#include "TabButtonWidget.generated.h"




class UBaseButton;
class UInventoryWidget;

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UTabButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseButton> EquipmentTabButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseButton> QuestTabButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseButton> ConsumableTabButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UBaseButton> MiscTabButton;


private:
	/** Inventory Tab that is currently displayed */
	EInventoryWidgetTab CurrentTab = EInventoryWidgetTab::EIWT_Equipment;

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnEquipmentTabPressed();

	UFUNCTION()
	void OnQuestTabPressed();

	UFUNCTION()
	void OnConsumableTabPressed();

	UFUNCTION()
	void OnMiscTabPressed();

	void UpdateInventoryHUD();

public:
	FORCEINLINE EInventoryWidgetTab GetCurrentTab() const { return CurrentTab; }
	FORCEINLINE void SetCurrentTab(EInventoryWidgetTab Tab) { CurrentTab = Tab; }
	
};
