// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "System/CommonTypes.h"

#include "BaseArmour.generated.h"


/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UBaseArmour : public UBaseItem
{
	GENERATED_BODY()
	
public:
	/** What percentage of inflicted damage is ignored */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Armour")
	float DamageReduction = 0.0f;

	/** Type of armour's passive effect */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Armour")
	EPassiveArmour PassiveType = EPassiveArmour::EPA_None;

	/** Scaler value for the passive effect */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Armour")
	float PassiveMultiplier = 0.0f;
};
