// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseItem.h"
#include "BaseQuestItem.generated.h"


class AActor;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UBaseQuestItem : public UBaseItem
{
	GENERATED_BODY()

public:
	/** Name of the NPC who gave the player the item */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Quest")
	FText QuestGiver = FText::GetEmpty();

	/** Description of how this item is relevant to the quest */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Quest")
	FText ItemContext = FText::GetEmpty();
};
