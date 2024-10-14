// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BaseNPC.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/InventoryHUDInterface.h"
#include "Inventory/InventoryComponent.h"

// Sets default values
ABaseNPC::ABaseNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NPCInventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("NPCInventory"));
}

bool ABaseNPC::Interact(UInventoryComponent* Inventory)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact NPC called."));
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Character)
	{
		IInventoryHUDInterface* Interface = Cast<IInventoryHUDInterface>(Character);
		if (Interface)
		{
			Interface->OpenNPCInventory(NPCInventoryComponent);
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

