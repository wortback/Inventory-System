// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "System/CommonTypes.h"

#include "BaseConsumable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UBaseConsumable : public UBaseItem
{
	GENERATED_BODY()
	

public:
	/** What player's attribute does the consumable affect. Default is Health. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumables Stats")
	EAttributeType AttributeType = EAttributeType::EAT_Health;

	/** How the affected attribute is changed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Consumables Stats")
	EConsumableEffect EffectType = EConsumableEffect::ECE_InstantRegeneration;
};
