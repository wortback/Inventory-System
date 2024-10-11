// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class INVENTORYSYSTEM_API UBaseWeapon : public UBaseItem
{
	GENERATED_BODY()
	
public:
	/** Base Damage the weapon deals */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	int32 BaseDamage = 0;

	/** Attack per second */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	float AttackRate = 0.0f;

	/** Maximum radius of AoE spells */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	float MaximumAoERange = 0.0f;

	/** How often the weapon does a critical hit */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	float CritRate = 0.0f;

	/** Upon doing a critical hit, how big is the damage scaled from the base damage */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	float CritDamage = 0.0f;
};
