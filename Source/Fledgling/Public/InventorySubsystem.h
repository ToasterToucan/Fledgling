#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InventoryTypes.h"
#include "CombatTypes.h"
#include "InventorySubsystem.generated.h"

UCLASS()
class FLEDGLING_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// +++++++++++++++++++++++ SAVE/LOAD +++++++++++++++++++++++
	/** Save all inventory data to file and instance. */
	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void SaveInventory();

	/** Load all inventory data from file. **The inventory will never load from the instance. */
	UFUNCTION(BlueprintCallable, Category = "Save/Load")
	void LoadInventory();


	// +++++++++++++++++++++++ AMBER CARD CHOICE +++++++++++++++++++++++
	/** Get the amount of a certain card the player has chosen to use from an amber. Returns -1 on failure. */
	UFUNCTION(BlueprintCallable, Category = "Amber Card Choice")
	int NumChosenOfCardFromAmber(FName amber_name, int card_index);

	/** Turn three integer values -- the amount of each card option the player has taken - and encode it into a byte. */
	UFUNCTION(BlueprintCallable, Category = "Amber Card Choice")
	uint8 EncodeAmberCardChoices(int val0, int val1, int val2);

	/** Find an amber's index in the AmberCardChoice array. Returns -1 if not found. */
	UFUNCTION(BlueprintCallable, Category = "Amber Card Choice")
	int FindAmberInChoiceArray(FName amber_name);


	// +++++++++++++++++++++++ GET INV INFO AS INV ITEM +++++++++++++++++++++++
	/** Returns, in order, equipped Ambers, then Companions, then Weapons. */
	UFUNCTION(BlueprintCallable, Category = "Get Info as Inv Item")
	void GetAllEquipped(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapons);

	/** Returns, in order, unlocked (excluding equipped) Ambers, then Companions, then Weapons. */
	UFUNCTION(BlueprintCallable, Category = "Get Info as Inv Item")
	void GetAllUnlocked(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapons);

	// +++++++++++++++++++++++ GET INV INFO AS CARDS +++++++++++++++++++++++
	/** Returns an array of all of the cards the given amber will give to the player. Does NOT care whether the amber is currently equipped or not. */
	UFUNCTION(BlueprintCallable, Category = "Get Info as Cards")
	TArray<FCard> GetCardArrayOfAmber(FInvItem amber);

	/** Returns an array of all of the cards the given weapon will give to the player. Does NOT care whether the weapon is currently equipped or not. */
	UFUNCTION(BlueprintCallable, Category = "Get Info as Cards")
	TArray<FCard> GetArrayOfWeapon(FInvItem weapon);

	/** Returns an array of all of the cards the currently equipped items will give to the player. */
	UFUNCTION(BlueprintCallable, Category = "Get Info as Cards")
	TArray<FCard> GetFullLoadout();

	// +++++++++++++++++++++++ ITEM MANIP +++++++++++++++++++++++
	/** Unlocks a new item for the player. */
	UFUNCTION(BlueprintCallable, Category = "Item Manip")
	void UnlockItem(const FInvItem item);

	/** Equips an item that is ALREADY UNLOCKED to the player, by the item itself. If force_equip is false, fails out if there is no empty slot available. If force_equip is true, equips into equip_slot, which is 0 by default. */
	UFUNCTION(BlueprintCallable, Category = "Item Manip", meta=(ReturnDisplayName = "equipped"))
	bool EquipItem_Item(FInvItem item, bool force_equip = false, int equip_slot = 0);

	/** Equips an item that is ALREADY UNLOCKED to the player, by it's index in the unlocks array. If force_equip is false, fails out if there is no empty slot available. If force_equip is true, equips into equip_slot, which is 0 by default. */
	UFUNCTION(BlueprintCallable, Category = "Item Manip")
	bool EquipItem_Index(int index, bool force_equip = false, int equip_slot = 0);

	/** Unequips an item that is CURRENTLY EQUIPPED to the player, by the item itself. */
	UFUNCTION(BlueprintCallable, Category = "Item Manip")
	void UnequipItem_Item(FInvItem item);

	/** Unequips an item that is CURRENTLY EQUIPPED to the player, by its index in the equipped array. */
	UFUNCTION(BlueprintCallable, Category = "Item Manip")
	void UnequipItem_Index(int index);

	// +++++++++++++++++++++++ OPEN/CLOSE +++++++++++++++++++++++
	/** Opens the Inventory. */
	UFUNCTION(BlueprintCallable, Category = "Open/Close")
	void OpenInventory();

	/** Closes the Inventory. */
	UFUNCTION(BlueprintCallable, Category = "Open/Close")
	void CloseInventory();

	// +++++++++++++++++++++++ HELPERS +++++++++++++++++++++++
	/** Tries to find an empty slot in the given array. If none is found, returns -1. */
	int FindFirstEmptySpace(TArray<FInvItem> array);
};
