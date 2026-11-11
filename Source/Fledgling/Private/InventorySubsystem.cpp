// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySubsystem.h"
#include <cmath>

// +++++++++++++++++++++++ VARIABLES +++++++++++++++++++++++
// The card choices the player has made for each amber.
TArray<FAmberCardSelection> amber_card_choices;

// The player's currently equipped items.
TArray<FInvItem> equipped_ambers;
TArray<FInvItem> equipped_companions;
TArray<FInvItem> equipped_weapon;		// Stored in an array for consistency's sake. Also allows for future double weapon allowances!

// The player's unlocked items. EXCLUDES equipped items.
TArray<FInvItem> unlocked_ambers;
TArray<FInvItem> unlocked_companions;
TArray<FInvItem> unlocked_weapons;


// +++++++++++++++++++++++ SAVE/LOAD +++++++++++++++++++++++
/** Save all inventory data to file and instance. */
void UInventorySubsystem::SaveInventory() {
	// body
}

/** Load all inventory data from file. **The inventory will never load from the instance. */
void UInventorySubsystem::LoadInventory() {
	// body
}


// +++++++++++++++++++++++ AMBER CARD CHOICE +++++++++++++++++++++++
/** Get the amount of a certain card the player has chosen to use from an amber. Returns -1 on failure. */
int UInventorySubsystem::NumChosenOfCardFromAmber(FName amber_name, int card_index) {
	// Fail out if this is an invalid index.
	if (card_index < 0 || card_index > 2) { return -1; }

	// Get this amber's index in the choice array. Fail out if it was not found in the array.
	int choice_array_index = FindAmberInChoiceArray(amber_name);
	if (choice_array_index < 0) { return -1; }

	// Shift the card selection byte over so the wanted bits are rightmost, then extract just the 3 rightmost bits using a mask.
	return ((amber_card_choices[choice_array_index].value) >> card_index * 3) & 7;
}

/** Turn three integer values -- the amount of each card option the player has taken - and encode it into a byte. */
uint8 UInventorySubsystem::EncodeAmberCardChoices(int val0, int val1, int val2) {
	return val0 + (val1 << 3) + (val2 << 6);
}

/** Find an amber's index in the AmberCardChoice array. Returns -1 if not found. */
int UInventorySubsystem::FindAmberInChoiceArray(FName amber_name) {
	for (int i = 0; i < amber_card_choices.Num(); i++) {
		if (amber_card_choices[i].row_name == amber_name) { return i; }
	}

	return -1;
}


// +++++++++++++++++++++++ GET INV INFO AS INV ITEM +++++++++++++++++++++++
/** Returns, in order, equipped Ambers, then Companions, then Weapons. */
void UInventorySubsystem::GetAllEquipped(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapons) {
	// pass
}

/** Returns, in order, unlocked (excluding equipped) Ambers, then Companions, then Weapons. */
void UInventorySubsystem::GetAllUnlocked(TArray<FInvItem>& Ambers, TArray<FInvItem>& Companions, TArray<FInvItem>& Weapons) {
	// pass
}

// +++++++++++++++++++++++ GET INV INFO AS CARDS +++++++++++++++++++++++
/** Returns an array of all of the cards the given amber will give to the player. Does NOT care whether the amber is currently equipped or not. */
TArray<FCard> UInventorySubsystem::GetCardArrayOfAmber(FInvItem amber) {
	// pass
}

/** Returns an array of all of the cards the given weapon will give to the player. Does NOT care whether the weapon is currently equipped or not. */
TArray<FCard> UInventorySubsystem::GetArrayOfWeapon(FInvItem weapon) {
	// pass
}

/** Returns an array of all of the cards the currently equipped items will give to the player. */
TArray<FCard> UInventorySubsystem::GetFullLoadout() {
	// pass
}

// +++++++++++++++++++++++ ITEM MANIP +++++++++++++++++++++++
/** Unlocks a new item for the player. */
void UInventorySubsystem::UnlockItem(const FInvItem item) {
	// pass
}

/** Equips an item that is ALREADY UNLOCKED to the player, by the item itself. If force_equip is false, fails out if there is no empty slot available. If force_equip is true, equips into equip_slot, which is 0 by default. */
bool UInventorySubsystem::EquipItem_Item(FInvItem item, bool force_equip, int equip_slot) {
	// pass
}

/** Equips an item that is ALREADY UNLOCKED to the player, by it's index in the unlocks array. If force_equip is false, fails out if there is no empty slot available. If force_equip is true, equips into equip_slot, which is 0 by default. */
bool UInventorySubsystem::EquipItem_Index(int index, bool force_equip, int equip_slot) {
	// pass
}

/** Unequips an item that is CURRENTLY EQUIPPED to the player, by the item itself. */
void UInventorySubsystem::UnequipItem_Item(FInvItem item) {
	// pass
}

/** Unequips an item that is CURRENTLY EQUIPPED to the player, by its index in the equipped array. */
void UInventorySubsystem::UnequipItem_Index(int index) {
	// pass
}

// +++++++++++++++++++++++ OPEN/CLOSE +++++++++++++++++++++++
/** Opens the Inventory. */
void UInventorySubsystem::OpenInventory() {
	// pass
}

/** Closes the Inventory. */
void UInventorySubsystem::CloseInventory() {
	// pass
}

// +++++++++++++++++++++++ HELPERS +++++++++++++++++++++++
/** Tries to find an empty slot in the given array. If none is found, returns -1. */
int UInventorySubsystem::FindFirstEmptySpace(TArray<FInvItem> array) {
	// pass
}