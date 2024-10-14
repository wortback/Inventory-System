// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InventorySystem/Public/Interfaces/InventoryHUDInterface.h"

#include "InventoryTestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInventoryComponent;
class UPrimaryHUDWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);


UCLASS(config=Game)
class AInventoryTestCharacter : public ACharacter, public IInventoryHUDInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Component that handles player's inventory */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* PlayerInventoryComponent;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenInventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PrimaryHUDWidgetClass;

	/* Primary HUD on top of which any other HUD such as Inventory etc is mounted */
	UPrimaryHUDWidget* PrimaryHUDWidget;

private:
	/** Actor the character is currently looking at */
	AActor* ViewedActor = nullptr;

	UInventoryComponent* NPCInventoryComp = nullptr;

public:
	AInventoryTestCharacter();
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for interacting input */
	void Interact(const FInputActionValue& Value);

	/** Called to open the inventory belonging to the character */
	void OpenInventory(const FInputActionValue& Value);


#pragma region InventoryHUDInterface
protected:
	virtual AActor* LookAt() override;

	virtual void OpenPlayerInventory() override;

	virtual void OpenNPCInventory(UInventoryComponent* NPCInventoryComponent) override;

	/** 
	* Depending on whether the character is trading with an NPC, updates PlayerInventoryWindow and NPCInventoryWindow
	* or the inventory menu */
	virtual void UpdateInventoryHUD() override;

	virtual void RemoveItem(F_InventoryItem* Item) override;

	virtual bool ProcessItem(F_InventoryItem* Item) override;

	virtual bool EquipItem(F_InventoryItem* Item) override;

	virtual bool SellItem(F_InventoryItem* Item) override;

	virtual bool BuyItem(F_InventoryItem* Item) override;

	virtual void UpdateNPCComponentPtr(UInventoryComponent* InventoryComp) override;

	virtual UInventoryComponent* GetInventoryComponent() const override { return PlayerInventoryComponent; }

private:
	/** Updates inventory menu */
	void UpdateInventoryHUD(UInventoryComponent* InventoryComponent);

	/** Updates PlayerInventoryWindow and NPCInventoryWindow */
	void UpdateInventoryHUD(UInventoryComponent* PlayerComp, UInventoryComponent* NPCComp);

#pragma endregion InventoryHUDInterface
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

