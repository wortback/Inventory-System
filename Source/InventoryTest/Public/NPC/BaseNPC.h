// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventorySystem/Public/Interfaces/InteractableInterface.h"

#include "BaseNPC.generated.h"

class UInventoryComponent;

UCLASS()
class INVENTORYTEST_API ABaseNPC : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	/** Component that handles player's inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* NPCInventoryComponent;

public:
	// Sets default values for this character's properties
	ABaseNPC();

	virtual bool Interact(UInventoryComponent* Inventory) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
